// simulation.c
#include "simulation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_random_seed() {
    srand((unsigned int)time(NULL));
}

int generate_random_time(int min, int max) {
    // Inicializa a semente aleatória se ainda não foi inicializada
    static int seed_initialized = 0;
    if (!seed_initialized) {
        initialize_random_seed();
        seed_initialized = 1;
    }

    // Gera um número aleatório no intervalo [min, max]
    return rand() % (max - min + 1) + min;
}

int generate_random_condition() {
    // Gera um número aleatório no intervalo [1, 5] para representar as condições
    return generate_random_time(1, 5);
}

int generate_patient_id() {
    static int id_counter = 1;
    return id_counter++;
}

int is_empty_exam_queue(Queue* queue) {
    return is_empty(queue);
}

void enqueue_exam(Queue* queue, ExamRecord exam) {
    enqueue(queue, exam);
}

ExamRecord dequeue_exam(Queue* queue) {
    return dequeue(queue);
}

void perform_exam(Simulation* sim, int time_step) {
    if (!is_empty(sim->patient_queue)) {
        ExamRecord patient_exam = dequeue_exam(sim->patient_queue);
        int patient_id = patient_exam.patient_id;
        int exam_duration = generate_random_time(5, 10);
        int condition = generate_random_condition();

        ExamRecord exam;
        exam.patient_id = patient_id;
        exam.timestamp = time_step;
        exam.condition = condition;

        enqueue_exam(sim->exam_queue, exam);
        log_event(sim->log, "Exame realizado para o paciente", patient_id, time_step);
    }
}

void perform_diagnosis(Simulation* sim, int time_step) {
    if (!is_empty_exam_queue(sim->exam_queue)) {
        ExamRecord exam = dequeue_exam(sim->exam_queue);
        int diagnosis_duration = generate_random_time(10, 30);

        // Lógica de realizar diagnóstico

        log_event(sim->log, "Laudo concluído para o paciente", exam.patient_id, time_step);
    }
}

void simulate_time_step(Simulation* sim, int time_step) {
    // Lógica para chegada de pacientes
    if (rand() % 100 < 20) {  // Probabilidade de 20%
        int patient_id = generate_patient_id();
        ExamRecord patient_exam;
        patient_exam.patient_id = patient_id;
        patient_exam.timestamp = time_step;  // Isso pode ser ajustado conforme necessário
        patient_exam.condition = generate_random_condition();  // Como mencionado, ajuste conforme necessário
        enqueue(sim->patient_queue, patient_exam);
        log_event(sim->log, "Novo paciente chegou ao hospital", patient_id, time_step);
    }

    // Lógica para realizar exames
    perform_exam(sim, time_step);

    // Lógica para realizar diagnósticos
    perform_diagnosis(sim, time_step);
}

Simulation* create_simulation() {
    Simulation* sim = (Simulation*)malloc(sizeof(Simulation));
    if (sim == NULL) {
        exit(EXIT_FAILURE);
    }

    sim->patient_queue = create_queue();
    sim->exam_queue = create_queue();
    sim->log = create_log();

    // Inicialize outras estruturas de dados necessárias

    return sim;
}

void update_and_print_metrics(Simulation* sim) {
    // Tempo médio de laudo
    int total_diagnosis_time = 0;
    int total_diagnosis_count = 0;

    // Tempo médio de laudo por patologia
    int diagnosis_time_by_condition[5] = {0};
    int diagnosis_count_by_condition[5] = {0};

    // Quantidade de exames realizados após o limite de tempo
    int late_diagnosis_count = 0;

    // Implemente a lógica para calcular as métricas
    // percorra a fila de exames realizados e atualize as métricas

    Node* current_node = sim->exam_queue->front;
    while (current_node != NULL) {
        ExamRecord current_exam = current_node->data;
        int diagnosis_time = generate_random_time(10, 30);

        total_diagnosis_time += diagnosis_time;
        total_diagnosis_count++;

        diagnosis_time_by_condition[current_exam.condition - 1] += diagnosis_time;
        diagnosis_count_by_condition[current_exam.condition - 1]++;

        if (diagnosis_time > 7200) {
            late_diagnosis_count++;
        }

        current_node = current_node->next;
    }

    // Calcule e imprima as métricasc
    double average_diagnosis_time = (double)total_diagnosis_time / total_diagnosis_count;
    printf("Tempo médio de laudo: %.2f unidades de tempo\n", average_diagnosis_time);

    for (int i = 0; i < 5; i++) {
        if (diagnosis_count_by_condition[i] > 0) {
            double average_diagnosis_time_condition = (double)diagnosis_time_by_condition[i] / diagnosis_count_by_condition[i];
            printf("Tempo médio de laudo para patologia %d: %.2f unidades de tempo\n", i + 1, average_diagnosis_time_condition);
        }
    }

    printf("Quantidade de exames realizados após o limite de tempo: %d\n", late_diagnosis_count);
}

void destroy_simulation(Simulation* sim) {
    destroy_queue(sim->patient_queue);
    destroy_queue(sim->exam_queue);
    destroy_log(sim->log);
    // Libere outras estruturas de dados necessárias
    free(sim);
}
