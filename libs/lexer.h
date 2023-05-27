// =============================================================================
// File: lexer.cpp
// Author: Gamaliel Marines Olvera
// Author: Rodrigo Terán Hernández
// =============================================================================

#include <sys/stat.h>
#include "./html.h"
#include "../utils.h"
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;
const int THREADS = 8;

// ===================================================================
// This function takes the time and runs all CS files into the lexer in
// sequential mode
//
// Parameters:
//  svector<string> TEST_CODE: All the CS filenames
//
// Returns:
// double seq_time: Total time it took to run the lexer
// ===================================================================
double run_seq(vector<string> TEST_CODE) {

    double seq_time = 0;

    cout << "Corriendo lexer en secuencial..." << endl;

    // Run multiple times
    for (int i = 0; i < N; i++) {
        start_timer();
        create_css_file(DIR_1);
        for(int j = 0; j < TEST_CODE.size(); j++) {
            // Create HTML
            create_html_file(TEST_CODE[j], j, DIR_1);
        };
        seq_time += stop_timer();
    };

    seq_time /= N;
    cout << "El tiempo de ejecución promedio del resaltador en modo secuencial es de: " << seq_time << " ms\n";
    cout << "Archivos resaltados: " << TEST_CODE.size() << endl << endl;
    return seq_time;
};

// ===================================================================
// This function takes the time and runs all CS files into the lexer in
// parallel mode
//
// Parameters:
//  svector<string> TEST_CODE: All the CS filenames
//
// Returns:
// double parallel_time: Total time it took to run the lexer
// ===================================================================
double run_parallel(vector<string> TEST_CODE) {

    double parallel_time = 0;
    Block blocks[THREADS];

    cout << "Corriendo lexer en paralelo..." << endl;

    int block_size = TEST_CODE.size() / THREADS;
    for(int i = 0; i < THREADS; i++){
        blocks[i].start = i * block_size;
        blocks[i].test_code = TEST_CODE;
        blocks[i].end = (i == THREADS - 1) ? TEST_CODE.size() : (i + 1) * block_size;
    };
    
    parallel_time = 0;
    pthread_t ptid[THREADS];

    // Run multiple times
    for (int i = 0; i < N; i++) {
        start_timer();
        for(int j = 0; j < THREADS; j++){
            pthread_create(&ptid[j], NULL, create_html_file_parallel, &blocks[j]);
        }

        for(int j = 0; j < THREADS; j++){
            pthread_join(ptid[j], NULL);
        }
        parallel_time += stop_timer();
    };

    parallel_time /= N;
    cout << "El tiempo de ejecución promedio del resaltador en modo paralelo es de: " << parallel_time << " ms\n";
    cout << "Archivos resaltados: " << TEST_CODE.size() << endl << endl;

    return parallel_time;
};