#include <stdio.h>
#include "global.h"
#include "miscell.h"


tdf_atpg() {
    printf("compress = %d, det_num = %d\n", compress, det_num);
    fptr undetect_fault;
    fptr fault_under_test;
    fptr f, ftemp;
    int current_detect_num, total_detect_num, i;
    int total_no_of_backtracks = 0;
    int current_backtracks;
    int no_of_aborted_faults = 0;
    int no_of_redundant_faults = 0;
    int no_of_calls = 0;
    /* function declaration */
    int tdf_podem();
    fptr transition_sim_a_vector();
    /* generate TDF fault list */
    generate_tdf_fault_list();
    fault_under_test = first_fault;
    undetect_fault = first_fault;
    /* TDF ATPG */
    while (fault_under_test) {
        switch (tdf_podem(fault_under_test, &current_backtracks)) {
            case TRUE:
                undetect_fault = fault_sim_a_vector(undetect_fault, &current_detect_num);
                total_detect_num += current_detect_num;
                in_vector_no++;
                break;
	    case FALSE:
                fault_under_test->test_tried = TRUE;
                fault_under_test->detect = REDUNDANT;
                no_of_redundant_faults++;
                break;
	    case MAYBE:
                fault_under_test->test_tried = TRUE;
                no_of_aborted_faults++;
                break;
        }
        fault_under_test = NULL;
        for (f = undetect_fault; f; f = f->pnext_undetect) {
            if (!f->test_tried) {
                fault_under_test = f;
                break;
            }
        }
        total_no_of_backtracks += current_backtracks; // accumulate number of backtracks
        no_of_calls++;
    }
}

int tdf_podem(fault, current_backtracks)
fptr fault;
int *current_backtracks;
{
    int podem();
    return podem(fault, current_backtracks);
}

