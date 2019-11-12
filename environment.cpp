//
// C++ Implementation by Ajay Bhaga
//

// MayaBrain shared libs
#include "environment.h"

cyclone::Random global_random;

// Method definitions
Environment::Environment() : Application()
{
    std::cout << "Evolution Manager -> starting..." << std::endl;
    EvolutionManager::getInstance()->startEvolution();

    // Create the random number generator
    random_d rd{0.0, 10.0f};


    // Create shape for each agent
    std::vector<std::shared_ptr<Agent>> agents = EvolutionManager::getInstance()->getAgents();
    for (int i = 0; i < agents.size(); i++) {

        agents[i]->setPosition(cyclone::Vector3(rd(), rd(), rd()));

        // Create agent -> collision sphere
        cyclone::CollisionSphere cs;
        cs.body = new cyclone::RigidBody();
        agentCollSpheres.emplace_back(cs);


        cs.radius = 0.25f;
        cs.body->setMass(5.0f);
        cs.body->setDamping(0.9f, 0.9f);
        cyclone::Matrix3 it;
        it.setDiagonal(5.0f, 5.0f, 5.0f);
        cs.body->setPosition(agents[i]->getPosition());
        cs.body->setInertiaTensor(it);
        cs.body->setAcceleration(cyclone::Vector3::GRAVITY);

        cs.body->setCanSleep(false);
        cs.body->setAwake(true);

    }
/*
    // Create the ball.
    agentCollSphere.body = new cyclone::RigidBody();
    ball.radius = 0.25f;
    ball.body->setMass(5.0f);
    ball.body->setDamping(0.9f, 0.9f);
    cyclone::Matrix3 it;
    it.setDiagonal(5.0f, 5.0f, 5.0f);
    ball.body->setInertiaTensor(it);
    ball.body->setAcceleration(cyclone::Vector3::GRAVITY);

    ball.body->setCanSleep(false);
    ball.body->setAwake(true);
*/
    /*
    // Test Case 1
    auto genotype = new Genotype();
    std::cout << "Generating random genotype..." << std::endl;
    genotype = genotype->generateRandom(10, 0.4, 20.4);
    genotype->outputToConsole();
    genotype->saveToFile("genotype01.data");
    std::cout << "Genotype saved to disk." << std::endl;

    std::cout << "Loading genotype from disk..." << std::endl;
    genotype = genotype->loadFromFile("genotype01.data");
    std::cout << "Loaded genotype from disk." << std::endl;
*/


    // Set up the initial block
    reset();
}

const char* Environment::getTitle()
{
    return "MayaBrain Demo";
}

void Environment::generateContacts() {
    hit = false;

    // Create the ground plane data
    cyclone::CollisionPlane plane;
    plane.direction = cyclone::Vector3(0, 1, 0);
    plane.offset = 0;

    // Set up the collision data structure
    cData.reset(maxContacts);
    cData.friction = (cyclone::real) 0.9;
    cData.restitution = (cyclone::real) 0.2;
    cData.tolerance = (cyclone::real) 0.1;

    // Perform collision detection
    cyclone::Matrix4 transform, otherTransform;
    cyclone::Vector3 position, otherPosition;

    for (int i = 0; i < this->agentCollSpheres.size(); i++) {

        for (Block *block = blocks; block < blocks + MAX_BLOCKS; block++) {
            if (!block->exists) continue;

            // Check for collisions with the ground plane
            if (!cData.hasMoreContacts()) return;
            cyclone::CollisionDetector::boxAndHalfSpace(*block, plane, &cData);

            if (ball_active) {
                // And with the sphere
                if (!cData.hasMoreContacts()) return;
                if (cyclone::CollisionDetector::boxAndSphere(*block, this->agentCollSpheres[i], &cData)) {
                    hit = true;
                    fracture_contact = cData.contactCount - 1;
                }
            }

            // Check for collisions with each other box
            for (Block *other = block + 1; other < blocks + MAX_BLOCKS; other++) {
                if (!other->exists) continue;

                if (!cData.hasMoreContacts()) return;
                cyclone::CollisionDetector::boxAndBox(*block, *other, &cData);
            }
        }

        // Check for sphere ground collisions
        if (ball_active) {
            if (!cData.hasMoreContacts()) return;
            cyclone::CollisionDetector::sphereAndHalfSpace(this->agentCollSpheres[i], plane, &cData);
        }
    }
}

void Environment::reset()
{
    // Only the first block exists
    blocks[0].exists = true;
    for (Block *block = blocks+1; block < blocks+MAX_BLOCKS; block++)
    {
        block->exists = false;
    }

    // Set the first block
    blocks[0].halfSize = cyclone::Vector3(4,4,4);
    blocks[0].body->setPosition(0, 7, 0);
    blocks[0].body->setOrientation(1,0,0,0);
    blocks[0].body->setVelocity(0,0,0);
    blocks[0].body->setRotation(0,0,0);
    blocks[0].body->setMass(100.0f);
    cyclone::Matrix3 it;
    it.setBlockInertiaTensor(blocks[0].halfSize, 100.0f);
    blocks[0].body->setInertiaTensor(it);
    blocks[0].body->setDamping(0.9f, 0.9f);
    blocks[0].body->calculateDerivedData();
    blocks[0].calculateInternals();

    blocks[0].body->setAcceleration(cyclone::Vector3::GRAVITY);
    blocks[0].body->setAwake(true);
    blocks[0].body->setCanSleep(true);


    ball_active = true;

    for (int i = 0; i < this->agentCollSpheres.size(); i++) {

        // Set up the agent
        this->agentCollSpheres[i].body->setOrientation(1, 0, 0, 0);
        this->agentCollSpheres[i].body->setVelocity(
                random.randomBinomial(4.0f),
                random.randomReal(1.0f, 6.0f),
                -20.0f
        );
        this->agentCollSpheres[i].body->setRotation(0, 0, 0);
        this->agentCollSpheres[i].body->calculateDerivedData();
        this->agentCollSpheres[i].body->setAwake(true);
        this->agentCollSpheres[i].calculateInternals();
    }

    hit = false;

    // Reset the contacts
    cData.contactCount = 0;
}

void Environment::update()
{
    Application::update();

    // Handle fractures.
    if (hit)
    {
        blocks[0].divideBlock(
            cData.contactArray[fracture_contact],
            blocks,
            blocks+1
            );
      ///  ball_active = false;
    }

    //std::cout << "test" << std::endl;

}

void Environment::updateObjects(cyclone::real duration) {
    for (Block *block = blocks; block < blocks + MAX_BLOCKS; block++) {
        if (block->exists) {
            block->body->integrate(duration);
            block->calculateInternals();
        }
    }


    // Iterate through agent controllers and apply update
    std::vector<std::shared_ptr<Agent>> agents = EvolutionManager::getInstance()->getAgents();
    std::vector<std::shared_ptr<AgentController>> controllers = EvolutionManager::getInstance()->getAgentControllers();
    for (int i = 0; i < controllers.size(); i++) {
        std::shared_ptr<AgentController> controller = controllers[i];
        controller->update();
    }


    std::cout << "Environment update objects";

    /*
    // Update position for each agent
    for (int i = 0; i < this->agentCollSpheres.size(); i++) {

        if (ball_active) {
            this->agentCollSpheres[i].body->integrate(duration);
            this->agentCollSpheres[i].calculateInternals();
            agents[i]->setPosition(this->agentCollSpheres[i].body->getPosition());
        }
    }*/

}

void Environment::display()
{
    const static GLfloat lightPosition[] = {0.7f,1,0.4f,0};

    Application::display();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_NORMALIZE);
    for (Block *block = blocks; block < blocks+MAX_BLOCKS; block++)
    {
        if (block->exists) block->render();
    }
    glDisable(GL_NORMALIZE);

    // Create the random number generator
    random_d rd{0.0, 1.0};
    for (int i = 0; i < this->agentCollSpheres.size(); i++) {
        if (ball_active)
        {
//            glColor3f(0.4f, 0.7f, 0.4f);
            glColor3f(rd(), rd(), rd());

            float size = rd();
            if (size < 0.3f) {
                size = 0.3f;
            }

            glPushMatrix();

            cyclone::Vector3 pos = this->agentCollSpheres[i].body->getPosition();
            glTranslatef(pos.x, pos.y, pos.z);
            glScalef(size, size, size);

            //glutSolidSphere(0.25f, 16, 8);
            glutSolidIcosahedron();
            glPopMatrix();
        }
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);

    // Draw some scale circles
    glColor3f(0.75, 0.75, 0.75);
    for (unsigned i = 1; i < 20; i++)
    {
        glBegin(GL_LINE_LOOP);
        for (unsigned j = 0; j < 32; j++)
        {
            float theta = 3.1415926f * j / 16.0f;
            glVertex3f(i*cosf(theta),0.0f,i*sinf(theta));
        }
        glEnd();
    }
    glBegin(GL_LINES);
    glVertex3f(-20,0,0);
    glVertex3f(20,0,0);
    glVertex3f(0,0,-20);
    glVertex3f(0,0,20);
    glEnd();

    Application::drawDebug();

    char buffer[255];

    std::vector<std::shared_ptr<Agent>> agents = EvolutionManager::getInstance()->getAgents();
/*    for (int i = 0; i < agents.size(); i++) {
        agents[i]->setPosition(cyclone::Vector3(rd(), rd(), rd()));
    }
*/
    sprintf(buffer, "Population: %d", agents.size());
    this->renderText(5, 5, buffer, NULL);
}

/**
 * Called by the common demo framework to create an application
 * object (with new) and return a pointer.
 */
Application* getApplication()
{
    return new Environment();
}