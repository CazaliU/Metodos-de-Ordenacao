
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// media de execução de cada metodo 3x
// arrumar print media
// vetor igual nas 3 execuções?

// Função para trocar dois elementos de um array
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble Sort
void bubbleSort(int arr[], int n, int *trocas, int *iteracoes) {
    int trocou;
    for (int i = 0; i < n - 1; i++) {
        trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*iteracoes)++;
            if (arr[j] > arr[j + 1]) {
                trocar(&arr[j], &arr[j + 1]);
                trocou = 1;
                (*trocas)++;
            }
        }
        if (trocou == 0) // Se nenhum elemento foi trocado, o array já está ordenado
            break;
    }
}

// Insertion Sort
void insertionSort(int arr[], int n, int *trocas, int *iteracoes) {
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        (*iteracoes)++;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
            (*trocas)++;
            (*iteracoes)++;
        }
        arr[j + 1] = chave;
    }
}

// Selection Sort
void selectionSort(int arr[], int n, int *trocas, int *iteracoes) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            (*iteracoes)++;
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            trocar(&arr[i], &arr[min_index]);
            (*trocas)++;
        }
    }
}

// Quick Sort
int partition(int arr[], int low, int high, int *trocas, int *iteracoes) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        (*iteracoes)++;
        if (arr[j] < pivot) {
            i++;
            trocar(&arr[i], &arr[j]);
            (*trocas)++;
        }
    }
    trocar(&arr[i + 1], &arr[high]);
    (*trocas)++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int *trocas, int *iteracoes) {
    if (low < high) {
        int pi = partition(arr, low, high, trocas, iteracoes);
        quickSort(arr, low, pi - 1, trocas, iteracoes);
        quickSort(arr, pi + 1, high, trocas, iteracoes);
    }
}



int main() {

    srand(time(NULL));
    int n; // Tamanho do array
    printf("Informe o tamanho do vetor a ser ordenado: \n");
    scanf("%d", &n);
    //int arr_bubble[n], arr_insertion[n], arr_selection[n], arr_quick[n];
    int *arr_bubble = (int*)malloc(n * sizeof(int));
    int *arr_insertion = (int*)malloc(n * sizeof(int));
    int *arr_selection = (int*)malloc(n * sizeof(int));
    int *arr_quick = (int*)malloc(n * sizeof(int));
    int x;

    int trocas_bubble, trocas_insertion, trocas_selection, trocas_quick, itr_b, itr_i, itr_s, itr_q;
    double bubble_time, insertion_time, selection_time, quick_time = 0;
    clock_t start, end;

    int opcao;
    printf("Digite 1 para acessar o gráfico de trocas ou 2 para o gŕafico de tempo:\n");
    scanf("%d", &opcao);
    
    for (int i = 0; i < 3; i++)
    {
        for (int i = 0; i < n; i++) {
        x = rand() % n;
        arr_bubble[i] = x;
        arr_insertion[i] = x;
        arr_selection[i] = x;
        arr_quick[i] = x;
    }
        // Bubble Sort
        trocas_bubble = 0;
        itr_b = 0;
        start = clock();
        bubbleSort(arr_bubble, n, &trocas_bubble, &itr_b);
        end = clock();
        bubble_time = ((double)(end - start) / CLOCKS_PER_SEC) + bubble_time;

        // Insertion Sort
        trocas_insertion = 0;
        itr_i = 0;
        start = clock();
        insertionSort(arr_insertion, n, &trocas_insertion, &itr_i);
        end = clock();
        insertion_time = ((double)(end - start) / CLOCKS_PER_SEC) + insertion_time;

        // Selection Sort
        trocas_selection = 0;
        itr_s = 0;
        start = clock();
        selectionSort(arr_selection, n, &trocas_selection, &itr_s);
        end = clock();
        selection_time = ((double)(end - start) / CLOCKS_PER_SEC) + selection_time;

        // Quick Sort
        trocas_quick = 0;
        itr_q = 0;
        start = clock();
        quickSort(arr_quick, 0, n - 1, &trocas_quick, &itr_q);
        end = clock();
        quick_time = ((double)(end - start) / CLOCKS_PER_SEC) + quick_time;


        if (opcao == 1){

            // Abra um arquivo temporário para escrever os dados
            FILE *dataFile = fopen("dados.txt", "w");
            if (dataFile == NULL) {
                perror("Erro ao abrir arquivo de dados");
                return 1;
            }

            // Escreva os dados no arquivo
            fprintf(dataFile, "Bubble-Insertion-Selection-Quick %d", trocas_bubble);
            fprintf(dataFile, "NULL %d", trocas_insertion);
            fprintf(dataFile, "NULL %d", trocas_selection);
            fprintf(dataFile, "NULL %d", trocas_quick);


            // Feche o arquivo
            fclose(dataFile);

            // Execute o Gnuplot para criar o gráfico
            FILE *gnuplot = popen("gnuplot -persistent", "w");
            if (gnuplot == NULL) {
                perror("Erro ao abrir o Gnuplot");
                return 1;
            }

            //Comandos Gnuplot para criar o gráfico
            fprintf(gnuplot, "set title 'Gráfico Comparativo'\n"); //cabeçalho
            fprintf(gnuplot, "set style data histograms\n"); 
            fprintf(gnuplot, "set style histogram clustered\n");
            fprintf(gnuplot, "set boxwidth 0.75\n"); // grossura coluna
            fprintf(gnuplot, "set xtic scale 0\n"); // stick do eixo x
            fprintf(gnuplot, "set yrange [0:*]\n"); // tamanho eixo y
            fprintf(gnuplot, "set ylabel 'Trocas'\n");
            //fprintf(gnuplot, "plot 'dados.txt' using 2:xtic(1) title 'BubbleSort', '' using 3 title 'Valor2'\n");
            fprintf(gnuplot, "plot 'dados.txt' using 2:xtic(1) title 'Bubble', '' using 3 title 'Insertion', '' using 4 title 'Selection', '' using 5 title 'Quick'\n");


            // Feche o Gnuplot
            fclose(gnuplot);
            break;
        }
    }

    if (opcao == 2){

        // Média de 3 excecuções
        double media_b, media_s, media_i, media_q;
        media_b = bubble_time/3;
        media_s = selection_time/3;
        media_i = insertion_time/3;
        media_q = quick_time/3;

        // Abra um arquivo temporário para escrever os dados
        FILE *dataFile = fopen("dados.txt", "w");
        if (dataFile == NULL) {
            perror("Erro ao abrir arquivo de dados");
            return 1;
        }

        // Escreva os dados no arquivo
        //fprintf(dataFile, "Media-Tempo %f", media);
        fprintf(dataFile, "Bubble-Insertion-Selection-Quick %f", media_b);
        fprintf(dataFile, "NULL %f", media_i);
        fprintf(dataFile, "NULL %f", media_s);
        fprintf(dataFile, "NULL %f", media_q);

        // Feche o arquivo
        fclose(dataFile);

        // Execute o Gnuplot para criar o gráfico
        FILE *gnuplot = popen("gnuplot -persistent", "w");
        if (gnuplot == NULL) {
            perror("Erro ao abrir o Gnuplot");
            return 1;
        }

        //Comandos Gnuplot para criar o gráfico
        fprintf(gnuplot, "set title 'Média de Três Execuções'\n"); //cabeçalho
        fprintf(gnuplot, "set style data histograms\n"); 
        fprintf(gnuplot, "set style histogram clustered\n");
        fprintf(gnuplot, "set boxwidth 0.75\n"); // grossura coluna
        fprintf(gnuplot, "set xtic scale 0\n"); // stick do eixo x
        fprintf(gnuplot, "set yrange [0:*]\n"); // tamanho eixo y
        fprintf(gnuplot, "set ylabel 'Tempo(s)'\n");
        //fprintf(gnuplot, "plot 'dados.txt' using 2:xtic(1) title 'Media'\n");
        fprintf(gnuplot, "plot 'dados.txt' using 2:xtic(1) title 'Bubble', '' using 3 title 'Insertion', '' using 4 title 'Selection', '' using 5 title 'Quick'\n");


        // Feche o Gnuplot
        fclose(gnuplot);
    }

        printf("\nBubble Sort: Trocas = %d, Iteracoes = %d, Media = %f segundos\n", trocas_bubble, itr_b, bubble_time);
        printf("\nInsertion Sort: Trocas = %d, Iteracoes = %d, Media = %lf segundos\n", trocas_insertion, itr_i, insertion_time);
        printf("\nSelection Sort: Trocas = %d, Iteracoes = %d, Media = %lf segundos\n", trocas_selection, itr_s, selection_time);
        printf("\nQuick Sort: Trocas = %d, Iteracoes = %d, Media = %lf segundos\n", trocas_quick, itr_q, quick_time);

    return 0;
}
