//Nghiem Nguyen

#include <stdio.h>
#include <stdlib.h>
#include<cstring>
#include "util.h"

int nextAction(char *Action, int *initialPosition, int *finalPosition) {
    char input[100];
    int returnAction;
    fgets(input, 100, stdin);
    returnAction = sscanf(input, "%s %d %d", Action, initialPosition, finalPosition);

        if (strcmp (Action, "Stop") == 0)                                       return 1;                           //perform Stop action when it is called
        if (strcasecmp(Action, "Instruction") == 0)                             return 1;                           //perform Instruction action when it is called
        if (strcasecmp(Action, "Instructions") == 0)                            return 1;                           //perform Instruction action when it is called
        if (strcmp(Action, "?") == 0)                                           return 1;                           //perform Instruction action when it is called
        if ((strcmp (Action, "PrintADJ") == 0) && (returnAction == 1))          return 1;                           //perform PrintADJ action when it is called

        if (strcmp (Action, "SinglePair") == 0) {                                                                   //perform Single Pair action when it is called
            if (sscanf(input, "%s %d %d", Action, initialPosition, finalPosition) == 3)  {
                return 1;
            } else {
                return 0;
            }            
        }

        if (strcmp (Action, "SingleSource") == 0) {                                                //perform SingleSource action when it is called
            if (sscanf(input, "%s %d", Action, initialPosition) == 2) {
                return 1;
            } else {
                return 0;
            }
        }

        if (strcmp (Action, "PrintLength") == 0) {                                                  //perform PrintLength action when it is called
            if (sscanf(input, "%s %d %d", Action, initialPosition, finalPosition) == 3) {
                return 1;
            } else {
                return 0;
            }
        }

        if (strcmp (Action, "PrintPath") == 0) {                                                    //perform PrintPath action when it is called
            if (sscanf(input, "%s %d %d", Action, initialPosition, finalPosition) == 3) {
                return 1;
            } else {
                return 0;
            }
        }

return 0;
}