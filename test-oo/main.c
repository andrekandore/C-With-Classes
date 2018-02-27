//
//  main.c
//  test-oo
//
//  Created by アンドレ on 2018/02/26.
//  Copyright © 2018年 アンドレ. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "class.h"

void _class_open(void);
void _class_close(void);

typedef struct _classFunctions {
    void (* const volatile open)(void);
    void (* const volatile close)(void);
} ClassFunctions;

typedef struct _class_variables {
    volatile char *name;
    volatile u_int age;
} ClassVariables;

typedef struct _class_constants {
    volatile const char *defaultName;
    volatile const u_int defaultAge;
} ClassConstants;

const volatile ClassConstants __class_constants = {.defaultName = "Unkown",.defaultAge = 18};

typedef struct _class {
    struct _class (* const volatile init)(struct _class);
    const volatile ClassFunctions functions;
    volatile ClassVariables variables;
    const volatile ClassConstants constants;
} Class;

void _class_open() {
    printf("%s \n",__PRETTY_FUNCTION__);
}

void _class_close() {
    printf("%s \n",__PRETTY_FUNCTION__);
}

Class _class_init(Class aClass);
Class _class_init(Class aClass){
    return aClass;
}

Class NewClass() {
    Class aClass = {.init = _class_init,
        .functions = (const volatile ClassFunctions){.open = _class_open,.close = _class_close},
        .variables = {(volatile char *)__class_constants.defaultName,__class_constants.defaultAge},
        .constants = __class_constants
    };
    return aClass;
}

Class *ClassByAllocation() {
    Class aClass = NewClass();
    Class *allocClass = (Class *)malloc(sizeof(Class));
    memcpy(allocClass,&aClass,sizeof(Class));
    return allocClass;
}

uint8_t fromStack(void *ptr) {
    int dummy = 1;
    return (ptr > (void *)&dummy ? 1 : 0);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n\n");

    Class aClass = NewClass();
    aClass.functions.open();
    aClass.functions.close();
    printf("'aClass Age' %d\n",aClass.variables.age);
    printf("'aClass Name' %s\n",aClass.variables.name);
    
    aClass.variables.age = 21;
    aClass.variables.name = "Johnny";
    
    printf("'aClass Age' %d\n",aClass.variables.age);
    printf("'aClass Name' %s\n",aClass.variables.name);
    
    printf("'aClass' On Stack? %d \n\n",fromStack(&aClass));

    
    
    Class *heapClass = ClassByAllocation();
    heapClass->functions.close();
    heapClass->functions.open();
    
    printf("'heapClass Age' %d\n",heapClass->variables.age);
    printf("'heapClass Name' %s\n",heapClass->variables.name);

    heapClass->variables.age = 21;
    heapClass->variables.name = "Johnny";
    
    printf("'heapClass Age' %d\n",heapClass->variables.age);
    printf("'heapClass Name' %s\n",heapClass->variables.name);

    
    printf("'heapClass' On Stack? %d \n\n",fromStack(heapClass));

    free(heapClass);
    
    return 0;
}
