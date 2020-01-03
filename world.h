#ifndef PLATRAY_WORLD_H
#define PLATRAY_WORLD_H

#include "entity_kind.h"
#include "player.h"

typedef struct Entity {
    void *object;
    EntityKind kind;
} Entity;

typedef struct EntityNode {
    Entity *entity;
    struct EntityNode *next;
} EntityNode;

typedef struct World {
    EntityNode *entities;
} World;

EntityNode *newEntityNode(Entity *entity);
Entity *newEntity(void *object, EntityKind kind);
void AddEntity(EntityNode **head, Entity *newEntity);
Player *GetPlayer(EntityNode *head);
void clearWorld(World *world);

#endif //PLATRAY_WORLD_H
