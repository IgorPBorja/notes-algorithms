<style>
body {
<!-- Reset the counter named theorem each time a body obj is instantiated-->
  counter-reset: theorem;
  counter-reset: claim;
}
h1 {
<!-- Reset the counter named theorem each time a h1 obj is instantiated-->
  counter-reset: theorem;
  counter-reset: claim;
}

p.theorem::before {
  counter-increment: theorem; 
  content: "Teorema " counter(theorem) " \2014 "; 
}
p.theorem[data-attribution]::before {
  content: "Teorema " counter(theorem) " (" attr(data-attribution) ")  \2014 ";
}

p.claim::before {
  counter-increment: claim; 
  content: "Afirmação " counter(claim) " \2014 "; 
}

p.claim[data-attribution]::before {
  content: "Afirmação " counter(claim) " (" attr(data-attribution) ")  \2014 ";
}
</style>

# Generic graph search
Entrada:

* Vértice inicial 
* Grafo 

Ideal: não olhar nenhum elemento mais do que um número limitado de vezes (isto é, da ordem de $O(|V| + |E|)$ ou melhor). 

## Algoritmo (ideia)
* Cada vértice deve estar associado a um booleano que indicará se já foi visitado.
* Marca-se o inicial, $s$, visitado.
* Enquanto possível:
	* Escolha uma aresta $(u,v)$ com $u$ visitado e $v$ não-visitado (fronteira): **se não existirem, termine execução**.
	* Marcar $v$ visitado

<p class="claim"> Ao fim do algoritmo, $v$ está marcado visitado se e só se existe um caminho $s \to v$ </p>
Prova: 
($\Rightarrow$) (invariante de loop): Um resultado mais forte que vamos mostrar é que essa condição não é satisfeita apenas ao término do algoritmo, mas é, de fato, uma invariante de loop: **ao final de cada iteração, o conjunto de vértices marcados visitados é um subconjunto daqueles alcançáveis a partir de** $s$.

* **Na inicialização**De fato, vale trivialmente no início do algoritmo, pois apenas $s$ foi visitado e existe um caminho de $s$ a ele mesmo: o caminho vazio. 
* **Manutenção**: Suponha que vale para a $k$-ésima iteração, portanto. Então na $k+1$-ésima iteração selecionamos uma aresta $(u,v) \in G$ com $u$ visitado e $v$ não. Como $u$ foi marcado como visitado na $k$-ésima iteração ou antes, existe (por hipótese de indução) um caminho $s, a_1, \dotsc, a_j, u$ da fonte $s$ a esse vértice. Portanto, quando $v$ é posto como visitado, a invariante de loop se mantém, pois existe o caminho $s, a_1, \dotsc, a_j, u, v$.  
* Portanto, ao término do algoritmo, a propriedade continua sendo válida.

($\Leftarrow$) Demonstração por contradição: suponha que, após o término do algoritmo, existe $v$ tal que $v$ não foi visitado e existe caminho $a_1, \dotsc, a_k$ de $s$ a $v$, isto é, com $a_1 = s, a_k = v$ e $(a_i, a_{i+1}) \in G, \ \forall 1 \leq i < k$. Como o subconjunto de índices dos vértices desse caminho (finito) que não foram visitados é não vazio (possui $k$), ele apresenta um menor elemento $j$ (com $j > 1$, pois $a_1 = s$ foi visitado).

Isto é, $a_{j-1}$ foi visitado, $a_j$ não foi e a aresta $(a_{j-1}, a_j)$ pertence a $G$. Porém isso é uma contradição, uma vez que o algoritmo não termina até não haverem mais arestas com o vértice de saída visitado e o de destino não-visitado. Isso finaliza a demonstração.

# Implementações do algoritmo anterior
Entretanto, o problema reside na linha:

"Escolha uma aresta $(u,v)$ com $u$ visitado e $v$ não-visitado (fronteira): **se não existirem, termine execução**."

Como escolher essa aresta de forma eficiente? Daí, surgem as implementações específicas, como BFS (Breadth-First-Search) e DFS (Depth-First-Search). 

## Breadth first Search 
Visita o grafo por camadas. Podemos definir as camadas de um grafo **não direcionado** em referência a um vértice $s$ recursivamente por:

* A camada $0$ contém apenas o vértice $s$
* A camada $n+1$ contém todos os vértices que
	* São adjacentes a um vértice de camada $n$
	* Não estão na camada $k$ para nenhum $0 \leq k \leq n$

Note uma correspondência direta entre essas camadas e os caminhos mais curto a partir da fonte $s$. De fato, denote por $d_s(v)$ a camada na qual se localiza o vértice $s$, pondo $\infty$ se não há tal camada, isto é, se $v$ não está conectado, por algum caminho, a $s$. 

<p class="claim"> O caminho mais curto de $s$ a $v$ possui comprimento $n+1$ (incluindo ambos no caminho) se e só se $v$ está na camada $n$</p>
Prova: 
Note que, se $d_s(u) = x$, e $(u, u')$ está no grafo, então $d_s(u') \leq x + 1$, com a igualdade se e só se $u'$ não está em nenhuma das camadas anteriores.

($\Rightarrow$) Seja $s, a_1, \dotsc, a_{n-1}, v$ esse caminho mínimo. Então temos que $a_1$ está na camada $1$, e portanto $d_s(a_2) \leq 2$. Indutivamente segue que $a_k \leq k$ para todo $ 2 \leq k \leq n - 1$. Consequentemente, devido à aresta $(a_{n-1}, v)$, $d_s(v) \leq d_s(a_{n-1}) + 1 = n$.

Suponha por contradição que ocorre a desigualdade estrita. Então existe $b_1$ com $d_s(b_1) < n - 1$. Indutivamente, segue que existe $b_i$ com $d_s(b_i) < n - i$ para todo $1 \leq i \leq n - 1$. Logo 

$$d_s(b_{n-1}) < 1 \implies d_s(b_{n-1}) = 0  \implies b_{n-1} = s$$

e portanto $s, b_{n-2}, \dotsc, b_1, v$ é um caminho de tamanho $n < n + 1$ de $s$ até $v$, o que contradiz a minimalidade do caminho anterior apresentado. 

($\Leftarrow$) Suponha que $d_s(v) = n$. Então, indutivamente, existe $a_i$ tal que $(a_i, a_{i-1})$ pertence ao grafo e $d_s(a_i) = n - i$, com $a_0 := v$. 

Logo, temos que $d_s(a_n) = 0 \implies a_n = s$, e assim $s, a_{n-1}, \dotsc, a_1, v$ é um caminho de $s$ a $v$. 

Por outro lado, suponha que existe um caminho mais curto $b_0 = s, b_1, \dotsc, b_{k-1}, b_{k} = v$ com $k < n + 1$. Então, como $d_s(b_1) = 1$, segue que (novamente por indução) $d_s(b_i) \leq i$, devido à aresta $(b_{i-1}, b_i)$ e à hipótese indutiva. Concluímos $d_s(b_k) = d_s(v) \leq k < n + 1$ contradição. Em outras palavras, o caminho de tamanho $n+1$ encontrado acima é mínimo.
