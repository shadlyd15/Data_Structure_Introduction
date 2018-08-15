/**
* @file  debug.h
* @brief Communication Module Debug Support
* @author  Shadly Salahuddin
* @date 18 -Jan - 2017
*/

#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PRINT_FUNC printf

// #define ENABLE_VERBOSE
#define ENABLE_DEBUG
#define COLORED_TEXT

#ifdef COLORED_TEXT
    #define RED   "\x1B[31m"
    #define GRN   "\x1B[32m"
    #define YEL   "\x1B[33m"
    #define BLU   "\x1b[34m"
    #define MAG   "\x1b[35m"
    #define CYN   "\x1B[36m"
    #define RESET "\x1B[0m"
#else
    #define RED
    #define GRN
    #define YEL
    #define BLU
    #define MAG
    #define CYN
    #define RESET
#endif  //COLORED_TEXT

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

    #ifdef ENABLE_DEBUG

        #define DEBUG_BAUDRATE  19200
        #define PLACE(x)        x
        #define PRINT(...)      do{PRINT_FUNC(__VA_ARGS__);} while(0)  //execute debug statement
        #define PRINTLN(...)    PRINT(__VA_ARGS__);  \
                                PRINT("\r\n")
        #define DEBUG_NEWLINE() PRINT("\r\n")

        #define ASSERT(expr)                                \
                if (expr) {                                 \
                   PRINTLN("");                             \
                   PRINT(GRN "[ASSERT OK] " RESET);         \
                   PRINT("( ");                             \
                   PRINT(#expr);                            \
                   PRINTLN(" ) is true;");                  \
                   DEBUG_POINT();                           \
                }                                           \
                else {                                      \
                   PRINTLN("");                             \
                   PRINT(RED "[ASSERT ERROR] " RESET);      \
                   PRINT("( ");                             \
                   PRINT(#expr);                            \
                   PRINTLN(" ) is false;");                 \
                   DEBUG_POINT();                           \
                }

        #define ASSERT_ARRAY(X, Y, N, fmt)                                   \
                    if(CMP_ARRAY(X, Y, N)){                                  \
                       PRINTLN("");                                          \
                       PRINT(GRN "[ARRAYS ARE EQUAL] " RESET);               \
                       PRINT(#X);                                            \
                       PRINT("[%d] = ", N);                                  \
                       PRINT(#Y);                                            \
                       PRINTLN("[%d]", N);                                   \
                       DEBUG_ARRAY(X, N, fmt);                           \
                       DEBUG_ARRAY(Y, N, fmt);                           \
                       DEBUG_POINT();                                        \
                    }                                                        \
                    else{                                                    \
                       PRINTLN("");                                          \
                       PRINT(RED "[ARRAYS ARE NOT EQUAL] " RESET);           \
                       PRINT(#X);                                            \
                       PRINT("[%d] != ", N);                                 \
                       PRINT(#Y);                                            \
                       PRINTLN("[%d]", N);                                   \
                       DEBUG_ARRAY(X, N, fmt);                           \
                       DEBUG_ARRAY(Y, N, fmt);                           \
                       DEBUG_POINT();                                        \
                    }

        bool CMP_ARRAY(uint8_t * array_1, uint8_t * array_2, uint8_t array_length) __attribute__((always_inline));

        bool CMP_ARRAY(uint8_t * array_1, uint8_t * array_2, uint8_t array_length) {\
                    for (uint32_t i = 0; i < array_length; i++) {\
                        if (array_1[i] != array_2[i]) {\
                            return false;\
                        }\
                    }\
                    return true;\
                }


        #define DEBUG_POINT() PRINT(YEL "[POINT] File : %s :: Function : %s :: Line : %d\n" RESET ,__FILENAME__, __func__, __LINE__)

        #define DEBUG(...)      PRINT(__VA_ARGS__)

        #define DEBUG_OK(...)       {   PRINT(GRN "[OK] " RESET);        \
                                        PRINTLN(__VA_ARGS__);   }

        #define DEBUG_ERROR(...)    {   PRINT(RED "[ERROR] " RESET);     \
                                        PRINTLN(__VA_ARGS__);   }

        #define DEBUG_ALERT(...)  {   PRINT(YEL "[ALERT] " RESET);   \
                                        PRINTLN(__VA_ARGS__);   }

        #define DEBUG_WARNING(...)  {   PRINT(BLU "[WARNING] " RESET);   \
                                        PRINTLN(__VA_ARGS__);   }

        #define DEBUG_ARRAY(array, length, format) \
            PRINT(CYN "[ARRAY] " RESET);\
            PRINT("uint8_t ");\
            PRINT(#array);\
            PRINT("[%d] = { ", length);\
            PLACE(for(int debugCount = 0; debugCount < length; debugCount++)) {\
                    PRINT(format, array[debugCount]); \
                    if(debugCount < (length -1))\
                        PRINT(", ");\
                  }\
            PRINT(" };\n")

        #define PRINT_ARRAY(str, array, length, format) \
            PRINT(GRN "[OK] " RESET);\
            PRINT("%s", str);\
            PLACE(for(int debugCount = 0; debugCount < length; debugCount++)) {\
                    PRINT(format, array[debugCount]); \
                  }\
            PRINT("\n")

        #define DEBUG_VALUE(VALUE, TYPE)  PRINT(CYN "[VALUE] " RESET);\
                                          PRINT(#VALUE);\
                                          DEBUG(" = ");\
                                          PRINTLN(TYPE, VALUE);\

        #define DEBUG_DIVIDER(CHAR, LENGTH) PRINT(YEL);\
                                            for(uint32_t i = 0; i < LENGTH; i++){\
                                                PRINT("%c", CHAR);\
                                            }\
                                            PRINT("\n");\
                                            PRINT(RESET);\

        #define THROW_EXCEPTION(...)    {   PRINT(RED "[EXCEPTION] " RESET); \
                                            PRINTLN(__VA_ARGS__);   \
                                            DEBUG_POINT();  }

    #else
        #define PLACE(x)
        #define PRINT(...)
        #define PRINTLN(...)
        #define DEBUG_NEWLINE()
        #define ASSERT(expr)
        #define DEBUG(...)
        #define DEBUG_ARRAY(str, array,length,format)
        #define PRINT_ARRAY(str, array, length, format)
        #define DEBUG_OK(...)
        #define DEBUG_ERROR(...)
        #define DEBUG_WARNING(...)
        #define DEBUG_VALUE(...)
        #define DEBUG_DIVIDER(CHAR, LENGTH)
        #define THROW_EXCEPTION(...)

    #endif //ENABLE_DEBUG

    #ifdef ENABLE_VERBOSE
        #define VERBOSE(x)  PLACE(x)
    #else
        #define VERBOSE(x)
    #endif //ENABLE_VERBOSE

#endif
