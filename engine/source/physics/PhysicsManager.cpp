#include "physics/PhysicsManager.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include "BulletCollision/BroadphaseCollision/btBroadphaseProxy.h"
#include "BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"
#include "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "LinearMath/btVector3.h"
#include "RigidBody.h"
namespace eng {

PhysicsManager::PhysicsManager() {}

PhysicsManager::~PhysicsManager() {}

void PhysicsManager::Init() {
  // Create bullet system, world and gravity
  m_broadPhase = std::make_unique<btDbvtBroadphase>();
  m_collisionConfig = std::make_unique<btDefaultCollisionConfiguration>();
  m_dispatcher =
      std::make_unique<btCollisionDispatcher>(m_collisionConfig.get());
  m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();
  m_world = std::make_unique<btDiscreteDynamicsWorld>(
      m_dispatcher.get(), m_broadPhase.get(), m_solver.get(),
      m_collisionConfig.get());
  m_world->setGravity(btVector3(0, -9.81f, 0));
}

void PhysicsManager::Update(float deltaTime) {
  const btScalar fixedTimeStep = 1.0f / 60.0f;
  const int maxSubsteps = 4;
  m_world->stepSimulation(deltaTime, maxSubsteps, fixedTimeStep);
}

btDiscreteDynamicsWorld* PhysicsManager::GetWorld() {
  return m_world.get();
}
void PhysicsManager::AddRigidBody(RigidBody* body) {
  if (!body || !m_world) {
    std::cout << "Null RigidBody to world" << std::endl;
    return;
  }
  if (auto rigidBody = body->GetBody()) {
    m_world->addRigidBody(rigidBody, btBroadphaseProxy::StaticFilter,
                          btBroadphaseProxy::AllFilter);
    body->SetAddedToWorld(true);

    std::cout << "Added RigidBody to world" << std::endl;
  }
}

void PhysicsManager::RemoveRigidBody(RigidBody* body) {
  if (!body || !m_world) {
    return;
  }
  if (auto rigidBody = body->GetBody()) {
    m_world->removeRigidBody(rigidBody);
    body->SetAddedToWorld(false);
  }
}
}  // namespace eng
