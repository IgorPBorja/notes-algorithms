<style>
body {
/*Reset the counter named theorem each time a body obj is instantiated*/
  counter-reset: theorem 0 definition 0 claim 0;
}
h1 {
/*Reset the counter named theorem each time a h1 obj is instantiated*/
  counter-reset: theorem 0 definition 0 claim 0; 
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

p.definition::before {
  counter-increment: definition; 
  content: "Definição  " counter(definition) " \2014 "; 
}

p.definition[data-attribution]::before {
  content: "Definição " counter(definition) " (" attr(data-attribution) ")  \2014 ";
}
</style>

# Generic graph search

Entrada:

- Vértice inicial
- Grafo

Ideal: não olhar nenhum elemento mais do que um número limitado de vezes (isto é, da ordem de $O(|V| + |E|)$ ou melhor).

## Algoritmo (ideia)

- Cada vértice deve estar associado a um booleano que indicará se já foi visitado.
- Marca-se o inicial, $s$, visitado.
- Enquanto possível:
  - Escolha uma aresta $(u,v)$ com $u$ visitado e $v$ não-visitado (fronteira): **se não existirem, termine execução**.
  - Marcar $v$ visitado

<strong> <p class="claim"> Ao fim do algoritmo, $v$ está marcado visitado se e só se existe um caminho $s \to v$ </p> </strong>
Prova:
($\Rightarrow$) (invariante de loop): Um resultado mais forte que vamos mostrar é que essa condição não é satisfeita apenas ao término do algoritmo, mas é, de fato, uma invariante de loop: **ao final de cada iteração, o conjunto de vértices marcados visitados é um subconjunto daqueles alcançáveis a partir de** $s$.

- **Na inicialização**De fato, vale trivialmente no início do algoritmo, pois apenas $s$ foi visitado e existe um caminho de $s$ a ele mesmo: o caminho vazio.
- **Manutenção**: Suponha que vale para a $k$-ésima iteração, portanto. Então na $k+1$-ésima iteração selecionamos uma aresta $(u,v) \in G$ com $u$ visitado e $v$ não. Como $u$ foi marcado como visitado na $k$-ésima iteração ou antes, existe (por hipótese de indução) um caminho $s, a_1, \dotsc, a_j, u$ da fonte $s$ a esse vértice. Portanto, quando $v$ é posto como visitado, a invariante de loop se mantém, pois existe o caminho $s, a_1, \dotsc, a_j, u, v$.
- Portanto, ao término do algoritmo, a propriedade continua sendo válida.

($\Leftarrow$) Demonstração por contradição: suponha que, após o término do algoritmo, existe $v$ tal que $v$ não foi visitado e existe caminho $a_1, \dotsc, a_k$ de $s$ a $v$, isto é, com $a_1 = s, a_k = v$ e $(a_i, a_{i+1}) \in G, \ \forall 1 \leq i < k$. Como o subconjunto de índices dos vértices desse caminho (finito) que não foram visitados é não vazio (possui $k$), ele apresenta um menor elemento $j$ (com $j > 1$, pois $a_1 = s$ foi visitado).

Isto é, $a_{j-1}$ foi visitado, $a_j$ não foi e a aresta $(a_{j-1}, a_j)$ pertence a $G$. Porém isso é uma contradição, uma vez que o algoritmo não termina até não haverem mais arestas com o vértice de saída visitado e o de destino não-visitado. Isso finaliza a demonstração.

# Implementações do algoritmo anterior

Entretanto, o problema reside na linha:

"Escolha uma aresta $(u,v)$ com $u$ visitado e $v$ não-visitado (fronteira): **se não existirem, termine execução**."

Como escolher essa aresta de forma eficiente? Daí, surgem as implementações específicas, como BFS (Breadth-First-Search) e DFS (Depth-First-Search).

# Breadth first Search

Visita o grafo por camadas. Podemos definir as camadas de um grafo (**direcionado ou não**) em referência a um vértice $s$ recursivamente por:

- A camada $0$ contém apenas o vértice $s$
- A camada $n+1$ contém todos os vértices que
  - São adjacentes a um vértice de camada $n$: isto é, existe $u$ na camada $n$ tal que existe a aresta $(u, v)$.
  - Não estão na camada $k$ para nenhum $0 \leq k \leq n$

Note uma correspondência direta entre essas camadas e os caminhos mais curto a partir da fonte $s$. De fato, denote por $d_s(v)$ a camada na qual se localiza o vértice $s$, pondo $\infty$ se não há tal camada, isto é, se $v$ não está conectado, por algum caminho, a $s$.

<strong> <p class="claim"> O caminho mais curto de $s$ a $v$ possui comprimento $n+1$ (incluindo ambos os extremos) se e só se $v$ está na camada $n$</p> </strong>
Prova:
Note que, se $d_s(u) = x$, e $(u, u')$ está no grafo, então $d_s(u') \leq x + 1$, com a igualdade se e só se $u'$ não está em nenhuma das camadas anteriores.

($\Rightarrow$) Seja $s, a_1, \dotsc, a_{n-1}, v$ esse caminho mínimo. Então temos que $a_1$ está na camada $1$, e portanto $d_s(a_2) \leq 2$. Indutivamente segue que $a_k \leq k$ para todo $ 2 \leq k \leq n - 1$. Consequentemente, devido à aresta $(a_{n-1}, v)$, $d_s(v) \leq d_s(a_{n-1}) + 1 = n$.

Suponha por contradição que ocorre a desigualdade estrita. Então existe $b_1$ com $d_s(b_1) < n - 1$. Indutivamente, segue que existe $b_i$ com $d_s(b_i) < n - i$ para todo $1 \leq i \leq n - 1$. Logo

$$d_s(b_{n-1}) < 1 \implies d_s(b_{n-1}) = 0  \implies b_{n-1} = s$$

e portanto $s, b_{n-2}, \dotsc, b_1, v$ é um caminho de tamanho $n < n + 1$ de $s$ até $v$, o que contradiz a minimalidade do caminho anterior apresentado.

($\Leftarrow$) Suponha que $d_s(v) = n$. Então, indutivamente, existe $a_i$ tal que $(a_i, a_{i-1})$ pertence ao grafo e $d_s(a_i) = n - i$, com $a_0 := v$.

Logo, temos que $d_s(a_n) = 0 \implies a_n = s$, e assim $s, a_{n-1}, \dotsc, a_1, v$ é um caminho de $s$ a $v$.

Por outro lado, suponha que existe um caminho mais curto $b_0 = s, b_1, \dotsc, b_{k-1}, b_{k} = v$ com $k < n + 1$. Então, como $d_s(b_1) = 1$, segue que (novamente por indução) $d_s(b_i) \leq i$, devido à aresta $(b_{i-1}, b_i)$ e à hipótese indutiva. Concluímos $d_s(b_k) = d_s(v) \leq k < n + 1$ contradição. Em outras palavras, o caminho de tamanho $n+1$ encontrado acima é mínimo.

## Implementação da BFS

```
BFS(graph G, start vertex s)
	visited[s] = true
	q = empty queue
	insert s in q
	while q is not empty:
		remove front node of q and call it v
		for each edge(v, w)
			if visited[w] is false:
				visited[w] = true
				insert w in q
```

## Corretude

<strong> <p class="claim"> (Invariante de loop) Em cada iteração, todo vértice em $q$ já foi visitado </p> </strong>
Prova:

- Inicialização: $q$ possui apenas o vértice $s$ quando criada, e esse vértice já foi marcado como visitado no início do código.
- Manutenção: elementos são adicionados na fila apenas na linha "insert w in q", a qual é precedida por marcar $w$ como visitado.
  A invariante, portanto, segue.

<strong> <p class="claim"> Ao final do algoritmo, um vértice foi visitado se e só se existe um caminho partindo de $s$ até ele </p> </strong>
Prova: devido à afirmação anterior, e ao `if` statment

`ìf visited[w] is false: ...`

toda aresta $(v, w)$ de fato percorrida pelo algoritmo satisfaz $visited[v] = true$ e $visited[w] = false$. Portanto, é um caso especial do modelo genérico da seção anterior, que já foi provado.

Isso mostra que a BFS visita um vértice se e só se ele está no componente conectado do vértice de origem, o que é exatamente o que queríamos demonstrar para mostrar a corretude da BFS.

## Característica de busca em largura

<strong> <p class="theorem"> Se $d_s(u) < d_s(v) < \infty$ então $u$ foi marcado como visitado antes de $v$. Isto é, os vértices são visitados em ordem crescente de camadas </p> </strong>
Prova:

Note que, como o vértice visitado é sempre aquele retirado da frente da fila, a ordem dos vértices visitados é a ordem dos vértices que entraram na fila: isto é, se os vértices foram visitados na ordem $v_{\sigma(1)}, \dotsc, v_{\sigma(n)}$, com $v_{\sigma(1)} = s$ evidentemente, então os vértices foram adicionados na fila nessa mesma ordem.

Assim, podemos agora seguir a demonstração por indução. O caso base é o grafo com um único vértice no componente conectado de $s$: o próprio $s$, e nesse caso o teorema é trivial. Suponha, então, válida a afirmação para todo grafo $M$ com $max_{v \in M}d_s(v) \leq n$. Seja então $G$ um grafo em que $max_{v \in G}d_s(v) = n + 1$.

Sejam $u_i, 1 \leq i \leq k$ os vértices que estão na $(n+1)$-ésima camada. Então cada $u_i$ é adicionado após visitar um vértice na $n$-ésima camada. Porém, pela hipótese de indução, os vértices no subgrafo $G_{u_1, \dotsc, u_k}$ são visitados em ordem crescente de camada e, portanto, visita-se $s$, depois todos os vértices da camada $1$ (em alguma ordem), $\dotsc$, depois todos os vértices da camada $n$, em alguma ordem. Assim, quando um vértice $u_i$ é adicionado no <strong>fim</strong> da fila, todos os vértices $v$ que satisfazem $d_s(v) \leq n$ já foram visitados (e removidos da fila) ou ainda estão na fila, na frente de $u_i$, e serão visitados primeiro por isso.

Logo, a propriedade do teorema se mantém para grafos de camada máxima $n+1$, provando-o por indução.

## Complexidade

<strong> <p class="theorem"> A complexidade da implementação acima do algoritmo de Breadth-First-Search é $O(|V_s| + |E_s|)$, onde $|V_s|$ é a quantidade de vértices no componente conectado de $s$ e $|E_s|$ a quantidade de arestas do componente conectado de $s$. </p> </strong>
Prova:
Podemos considerar o algoritmo agindo apenas no subgrafo que representa o componente conectado que contém $s$, pois pela Afirmação 2 da seção "Corretude", um vértice é visitado se e só se ele está nesse componente. Ademais, uma aresta que não faz parte desse componente que contém $s$ envolve, necessariamente, dois vértices que não fazem parte desse componente e, com isso, nunca poderia ter sido analisada. Com isso, temos:
<strong> <p class="claim"> Todo vértice é visitado somente uma vez </p></strong>

<div style="margin-left: 3%;">
Se $v$ fosse visitado duas ou mais vezes, isso quer dizer que ele foi colocado (pelo menos) uma segunda vez na fila, isto é, existem duas arestas $e_1 = (u_1, v)$ e $e_2 = (u_2, v)$ que o algoritmo visita e que foram usadas para inserir $v$ na fila. Suponha sem perda de generalidade que $e_1$ é analisada antes de $e_2$. Então ao analisar $e_1$ e inserir $v$ na fila, $v$ é marcado como visitado.

Porém isso implica que, olhando para as adjacências de $u_2$, o algoritmo inseriu $v$ com $visited[v] = true$, o que contradiz a implementação dada! Logo cada vértice só pode ser visitado uma única vez.

Note que podemos ter inclusive $u_1 = u_2$ (no caso de múltiplas arestas entre dois vértices) e demonstração continua valendo da mesma maneira.

</div>

<strong><p class="claim"> Cada aresta é analisada uma única vez</p></strong>

<div style="margin-left: 3%;">
Seja $(u,v) \in E_s$ uma aresta com, sem perda de generalidade, $u$ sendo visitado primeiro que $v$. Então a aresta é analisada (apenas uma única vez) quando o algoritmo está iterando sobre a adjacência de $v$ e, nesse instante, $v$ é marcado visitado. Note que, pela afirmação anterior, $u$ não é visitado novamente, e portanto a aresta $(u,v)$ não é mais analisada a partir de $u$ - o que já é suficiente para finalizar a demonstração, no caso de grafos direcionados.

<em>No caso do grafo ser não-direcionado</em>, basta observar que, ao visitar $v$ e iterar sobre sua adjacência, como $u$ já foi marcado como visitado, o algoritmo não vai passar pela aresta $(v,u)$.

</div>
Portanto, segue que a complexidade do algoritmo é $O(|V_s| + |E_s|)$ como queríamos demonstrar.

# Calculando componentes conectados em grafos não direcionados com BFS

## Por que "não-direcionado"?: definindo e entendendo componentes conectados

Intuitivamente, pensamos em componentes conectados como as "peças" de um grafo: conjunto de vértices que estão todos interligados. Mais precisamente, queremos que, dentro de um mesmo componente conectado, entre quaisquer dois vértices sempre exista um caminho.

Entretanto, conforme veremos, essa ideia, ao ser aplicada para grafos <strong>direcionados</strong>, não é compatível com a definição que daremos a seguir, a qual é a mais útil para os algoritmos de conectividade a seguir.

<strong><p class="definition"> Dados dois vértices $u, v$, definimos a relação de equivalência $\sim$ por: $u \sim v \iff \text{ existe um caminho de } u \text{ até } v$</p></strong>

<strong><p class="theorem"> Para grafos <em>não direcionados</em>, a relação $\sim$ definida acima é uma relação de equivalência.</p></strong>
Prova: para todo o grafo, direcionado ou não, temos que $\sim$ é reflexiva (basta considerar o caminho sem arestas) e é transitiva, pois se $u \sim v$ com um caminho $u \to a_1 \to \dotsc \to a_n \to v$ e $v \sim w$ com um caminho $v \to b_1 \to \dotsc \to b_m \to w$, então $u \sim w$ com o caminho
$$u \to a_1 \to \dotsc a_n \to v \to b_1 \to \dotsc \to b_m \to w$$

Porém, se $u \sim v$, apenas para grafos <strong>não direcionados</strong> teremos necessariamente $v \sim u$ (cujo caminho associado é o mesmo de $u$ a $v$, com o sentido das arestas invertidas). De fato, para grafos direcionados temos o contra-exemplo simples do seguinte grafo-linha: $G_1 = (V_1, E_1)$ com
$V_1 = {1, 2, 3}$
$E_1 = {(1, 2), (2, 3)}$

Agora, podemos definir os componentes conectados.
<strong><p class="definition"> Dado um grafo $G = (V, E)$ definimos seus componentes conectados como o conjunto quociente $V/\sim$</p></strong>

## Implementação e análise

```
connected_components(Graph G)
	for s in V:
		if visited[s] is false:
			BFS(G, s)
```

Esse algoritmo garantidamente visita todos os vértices e arestas de $G$, devido à BFS visitar todos os vértices (e, logo, arestas) do componente conectado de $v$, e marcá-los como visitados.

<strong><p class="theorem"> Esse algoritmo é $O(|V| + |E|) </p></strong>
Prova: se $G$ possui $k$ componentes conectados $G_1,\dotsc, G_k$, então para todo $G_i$ com $1 \leq i \leq k$, na primeira vez em que se realizar a BFS em um vértice desse componente, todos os seus vértices são marcados como visitados, e portanto nenhuma BFS visitará esse componente de novo.

Isso mostra que exatamente $k$ BFSs são realizadas, cada uma com complexidade $O(|V_i| + |E_i|)$, onde $|V_i|$ e $|E_i|$ são a quantidade de vértices e arestas do $i$-ésimo componente. Assim

$$O(connected\_components) = \sum_{1 \leq i \leq k}O(|V_k| + |E_k|) = O(\sum_{1 \leq i \leq k}|V_k| + \sum_{1 \leq i \leq k}|E_k|) = O(|V| + |E|)$$
mostrando que o algoritmo é $O(|V| + |E|)$, como queríamos.

## Adaptações

Todas as adaptações a seguir mantém a complexidade do algoritmo intacta.

### Calculando o número de componentes conectados

```
connected_components(Graph G)
	num = 0
	for s in V:
		if visited[s] is false:
			BFS(G, s)
			num = num + 1
	return num
```

### Calculando o tamanho de cada componente conectado

```
BFS_measure_component(graph G, start vertex s)
	component_size = 0
	visited[s] = true
	q = empty queue
	insert s in q
	while q is not empty:
		remove front node of q and call it v
		for each edge(v, w)
			if visited[w] is false:
				visited[w] = true
				component_size = component_size + 1
				insert w in q
	return component_size

connected_components(Graph G)
	sizes = []
	for s in V:
		if visited[s] = false:
			insert BFS_measure_component(G, s) in sizes
	return sizes
```

Essa implementação adiciona a repetição da operação de adicionar um elemento ao vetor $sizes$ um total de $k$ vezes, em que $k$ é a quantidade de componentes conectados. Como $k \leq |V|$, temos que essa implementação é $O(|V| + |E| + k) = O(|V| + |E|)$ como todas as outras.

### Calculando os componentes conectados em si

```
BFS_get_component(graph G, start vertex s)
	component = []
	visited[s] = true
	q = empty queue
	insert s in q
	while q is not empty:
		remove front node of q and call it v
		for each edge(v, w)
			if visited[w] is false:
				visited[w] = true
				insert w in component
				insert w in q
	return component

connected_components(Graph G)
	components = []
	for s in V:
		if visited[s] = false:
			insert BFS_get_component(G, s) in components
	return components
```

A diferença dessa implementação é que cada vértice é inserido exatamente uma vez (na BFS do seu respectivo componente), e cada componente (vetor) é adicionado uma vez à matriz $components$ - o que gera mais $O(|V| + k)$ operações, em que $k$ é a quantidade de componentes conectados. Como $k \leq |V|$, o algoritmo é $O(|V| + |E| + |V| + k) = O(|V| + |E|)$, como todas as outras implementações.


## DFS: Depth-First-Search
### Implementação com stack <em>explícito</em>
```
dfs(graph G, source s)
	visited = [false, ..., false] with |V| elements
	p = new stack
	p.push(s)
	while (p is not empty):
		u = p.top
		visited[u] = true
		p.pop() // remove last element from the stack
		for each edge (u,v) in G:
			if (visited[v] is false):
				p.push(v)
```

### Implementação recursiva (com stack <em>implícito</em>)
```
visited = [false, ..., false] with |V| elements
dfs(graph G, source u, visited[]):
	visited[u] = true
	for each edge (u, v) in G:
		if (visited[v] is false):
			dfs(v)
	
dfs(G, s, visited[])
```


