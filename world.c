#include <stdlib.h>
#include <stdio.h>
#include "world.h"

void AddEntity(EntityNode **head, Entity *newEntity) {
    EntityNode *currNode = *head;
    EntityNode *newNode = newEntityNode(newEntity);

    if (currNode) {
        while (currNode->next) {
            currNode = currNode->next;
        }

        currNode->next = newNode;
    } else {
        *head = newNode;
    }
}

EntityNode *newEntityNode(Entity *entity) {
    EntityNode *newNode = (EntityNode *) malloc(sizeof(EntityNode));

    if (newNode) {
        newNode->entity = entity;
        newNode->next = 0;
    } else {
        printf("Could not allocate memory (newEntityNode)\n");
        exit(-1);
    }

    return (newNode);
}

Entity *newEntity(void *object, EntityKind kind) {
    Entity *new = (Entity *) malloc(sizeof(Entity));

    if (new) {
        new->object = object;
        new->kind = kind;
    } else {
        printf("Could not allocate memory (newEntity)\n");
        exit(-1);
    }

    return (new);
}

Player *GetPlayer(EntityNode *head) {
    EntityNode *currNode = head;

    while (currNode) {
        if (currNode->entity->kind == PLAYER)
            return ((Player *)currNode->entity->object);
        currNode = currNode->next;
    }

    return (0);
}