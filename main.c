#include "simulation.h"  // Módulo principal da simulação
#include "log.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Inicializa a semente para números aleatórios

    Simulation *sim = create_simulation();
    
    // Loop principal da simulação
    for (int time_step = 0; time_step < 43200; time_step++) {
        simulate_time_step(sim, time_step);
        
        // A cada 10 unidades de tempo, atualize e imprima as métricas
        if (time_step % 10 == 0) {
            update_and_print_metrics(sim);
        }
    }

    save_log_to_file(sim->log, "log.txt");  // Salva o log no arquivo

    destroy_simulation(sim);  // Libera a memória alocada

    return 0;
}
