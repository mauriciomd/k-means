# K-means

Repositório utilizado para apresentação e armazenamento das tarefas da disciplina ELC893 - Programação de Alto Desempenho/PGCC-UFSM.


## Implementações
 Há duas implementações simples do algoritmo de [K-means](https://www.datascience.com/blog/k-means-clustering), ambas utilizando C++:
 - k-means.cpp: versão sequencia do algoritmo. O programação recebe como entrada um arquivo texto, com colunas separadas por espaço, e o número de clusters.
 - k-means-openmp.cpp: versão paralela do algortimo utilizando [OpenMP](https://www.openmp.org/). Esta versão recebe os mesmos argumentos da versão sequencial, porém o número de threads pode ser controlado através da variável de ambiente OMP_NUM_THREADS=<número de threads>. A paralelização foi realizada dividindo o dataset entre as várias threads. Assim, cada thread é responsável por calcular a distância eucliadiana de N pontos até as centróides informadas na entrada.
 
 
## Experimentos


## Literatura
