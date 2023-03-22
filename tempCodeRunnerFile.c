    // FILE *batch = NULL;
    // char command[MAX_BUFFER];
    // if(argc > 1){
    //     batch = fopen(argv[1], "r");
    //     if(!batch){
    //         printf("error opening batch file\n");
    //         return 1;
    //     }
    // }

    // while(1){
    //     if(batch){
    //         if(!fgets(command, MAX_BUFFER, batch)){
    //             //end of file reached
    //             break;
    //         }
    //     } else {
    //         printf("%s", prompt);
    //         if(!fgets(command, MAX_BUFFER, stdin)){
    //             //end of input reached
    //             break;
    //         }
    //     }

    //     command[strcspn(command, "\n")] = '\0';
    //     printf("Command: %s", command);
    // }
    //     if(batch){
    //         fclose(batch);
    //     }
    //     return 0;