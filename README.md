# K-means

Repositório utilizado para apresentação e armazenamento das tarefas da disciplina ELC893 - Programação de Alto Desempenho/PGCC-UFSM.


## Implementações
 Há duas implementações simples do algoritmo de [K-means](https://www.datascience.com/blog/k-means-clustering), ambas utilizando C++:
 - k-means.cpp: versão sequencial do algoritmo. O programação recebe como entrada um arquivo texto, com colunas separadas por espaço, e o número de clusters.
 - k-means-openmp.cpp: versão paralela do algortimo utilizando [OpenMP](https://www.openmp.org/). Esta versão recebe os mesmos argumentos da versão sequencial, porém o número de threads pode ser controlado através da variável de ambiente OMP_NUM_THREADS=<número de threads>. A paralelização foi realizada dividindo o dataset entre as várias threads. Assim, cada thread é responsável por calcular a distância eucliadiana de N pontos até as centróides informadas na entrada.
 
 
## Experimentos


## Literatura
Esta seção tem como objetivo apresentar algumas implementações paralelas do algoritmo de K-means, as quais podem ser encontradas na literatura.

- Em [Farivar, Reza, et al.](https://pdfs.semanticscholar.org/0638/dc0565cb11191ab1e2b91cd19b630cfa8c34.pdf), os autores realizaram uma implementação do algoritmo para execução em GPUs, utilizando NVIDIA CUDA SDK. Nesta implementação, cada thread da GPU é responsável por um único ponto, de modo a calcular a distância entre o ponto até os K clusters e assinalar o ponto ao cluster mais perto. De acordo com os experimentos realizados pelos autores, esta implementação obteve um aumento de 13x no desempenho quando comparado à implementação base.

- No trabalho desenvolvido por [Zhao, Weizhong, Huifang Ma, and Qing He](https://www.researchgate.net/profile/Qing_He6/publication/225695804_Parallel_K-Means_Clustering_Based_on_MapReduce/links/5768a0f508ae8ec97a424884.pdf), é apresentado uma implementação de K-means baseada no MapReduce. Na fase de Map os pontos são assinalados ao cluster mais próximo, enquanto que na fase de Reduce, é realizado a atualização da posição dos clusters. A fim de reduzir o custo de comunicação, os outosres propuseram uma função intermediária lidar com a combinação parcial dos valores intermediários com a mesma chave dentro da mesma tarefa do mapa. Segundo os autores, os resultados demonstram que o algoritmo proposto pode escalar bem e processar eficientemente grandes conjuntos de dados.

- No artigo proposto por [Joshi, Manasi N.](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.101.1882&rep=rep1&type=pdf), é proposta uma implementação do algoritmo em sistemas de memmória distribuída multiprocesados, utilizando MPI para a comunicação. Nesta abordagem, cada processo é responsável por computar a distância de N = M/número_de_processos (onde M é o tamanho do dataset) pontos e assinar cada ponto ao cluster de menor distância. De acordo com o autor não foi possível alcançar níveis ótimos de speedup, no entanto foram observados benefícios na paralelização do algoritmo.
