<style>
body {
/*Reset the counter named theorem each time a body obj is instantiated*/
  counter-reset: theorem 0 definition 0 claim 0 lemma 0;
}
h1 {
/*Reset the counter named theorem each time a h1 obj is instantiated*/
  counter-reset: theorem 0 definition 0 claim 0 lemma 0; 
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

p.lemma::before {
  counter-increment: lemma; 
  content: "Lema " counter(lemma) " \2014 "; 
}
p.lemma[data-attribution]::before {
  content: "Lema " counter(lemma) " (" attr(data-attribution) ")  \2014 ";
}

div.proof{
  margin-left: 3%;
}
</style>
<script>
  let qed = document.createElement("div");
  qed.innerHTML = "$\qed$";
  qed.style = "float:right;";
  
  proof_div_array = document
                    .getElementsByClassName("proof");
  for (var d in proof_div_array){
    d.after(qed);
  }
</script>

# Topological sort - introdução

## Definição

<strong> <p class="definition"> Dado um grafo direcionado $G = (V, E)$, uma ordenação topológica é uma bijeção $f : V \to \{1, \dotsc, |V|\}$ tal que $(u, v) \in E \implies f(u) < f(v)$. </p> </strong>

## Conceitos importantes em grafos direcionados

<strong><p class="definition" id="def-indegree"> Em um grafo direcionado, definimos o grau de entrada (<em>indegree</em>) de um vértice como a quantidade de arestas que o tem como extremidade final. Isto é, dado um grafo $G = (V, E)$ e um vértice $v \in V$ temos que o grau de entrada é
$$\deg^{-}(v) |\{u \in V|\ (u, v) \in E\}|$$

</p></strong>

<strong><p class="definition"> Em um grafo direcionado, definimos o grau de saída (<em>outdegree</em>) de um vértice como a quantidade de arestas que o tem como extremidade inicial. Isto é, dado um grafo $G = (V, E)$ e um vértice $v \in V$ temos que o grau de entrada é
$$\deg^{+}(v) |\{u \in V|\ (v, u) \in E\}$$

</p></strong>

<strong><p class="theorem"> Para todo grafo direcionado $G = (V, E)$:
$$\sum_{v \in V}\deg^{+}(v) = \sum_{v \in V}\deg^{-}(v) = |E|$$

</p></strong>

### Source e sink

<strong><p class="definition"> Um vértice $v$ é uma <em>source</em> se seu grau de entrada é $0$. Isto é
$$\deg^{-}(v) = 0$$

</p></strong>

<strong><p class="definition"> Um vértice $v$ é uma <em>sink</em> se seu grau de saída é $0$. Isto é
$$\deg^{+}(v) = 0$$

</p></strong>

<strong><p class="lemma"> Todo grafo direcionado <em>acíclico</em> (DAG) possui pelo menos uma <em>source</em> e pelo menos uma <em>sink</em>.

</p></strong>

<em>Prova:</em><div class="proof">
Provamos, por contradição, a existência de uma <em>sink</em>: o outro caso é análogo.

Suponha que todo vértice possui grau de saída não-nulo e tome um vértice $v_0 \in V$. Considere a sequência $(v_i)_{i \in \N}$ definida recursivamente da seguinte forma: $v_{i+1}$ é um vértice qualquer no conjunto de vértices para os quais saem arestas de $v_i$.

Como o conjunto de vértices é finito, e essa sequência é infinita, existem dois índices $i < j$ tal que $v_i = v_j$. Logo, existe um caminho $v_i \to v_{i+1} \to \dotsc \to (v_j = v_i)$ de $v_i$ nele mesmo, o que é, por definição, um ciclo. Isso contradiz o fato do grafo ser acíclico.

Logo existe um vértice com grau de saída nulo: uma <em>sink</em>.

</div>

## Existência

<strong> <p class="theorem"> Um grafo direcionado tem uma ordenação topológica se e somente se ele é <em>acíclico</em> (os chamados "directed acyclic graphs" ou DAGs). </p></strong>
<em> Prova: </em> <div class="proof">
$(\Rightarrow)$ Seja $f$ uma tal ordenação topológica e $u_1, \dotsc, u_n$ um ciclo. Então temos, pela definição de ordenação topológica, que
$$f(u_1) < f(u_2) < \dotsc < f(u_n) < f(u_1)$$
contradição! Logo, ser um DAG é condição <strong> necessária</strong>.

$(\Leftarrow)$
Dado um grafo $G = (V, E)$ e $v \in V$, denote por $G_v$ o subgrafo obtido removendo o vértice $v$ e todas as arestas da qual ele participa. Note que, ao remover vértices de um DAG, continuamos com um DAG, e portanto temos a seguinte solução:

<div class="pseudocode">

topological_sort(DAG $G$)

> find a sink vertex $v$ of $G$

> $f(v) \gets$ number of vertices of $G$

> topological_sort($G_v$)

</div>

<strong><p class="claim"> Esse algoritmo gera uma ordenação topológica

</p></strong>
<em>Prova:</em> <div class="proof">
Como remover vértices de um DAG mantém o grafo como DAG, segue que sempre - enquanto o grafo atual não estiver vazio - existe um vértice <em>sink</em>.

Dessa forma, se $G = (V, E)$ é o grafo em questão, ao final do algoritmo temos uma função $f$ que satisfaz $f(V) = \{1, \dotsc, |V|\}$ (isto é, é uma bijeção do conjunto de vértice para o conjunto de labels de $1$ a $|V|$).

Para mostrar que essa bijeção é uma ordenação topológica, temos que para todo vértice $v \in V$, se $f(v) = i$, então $v$ é uma <em>sink</em> no subgrafo de $i$ vértices obtido removendo os vértices $f^{-1}(i+1), \dotsc, f^{-1}(|V|)$. Ou seja, para toda aresta $(v, u)$ (aresta que parte de $v$), temos $f(u) \in {i+1, \dotsc, |V|} \implies f(v) = i < f(u)$

Isso mostra que $f$ é uma ordenação topológica.

  </div>

Portanto, a partir dessa demonstração por construção concluímos que toda DAG possui uma ordenação topológica.

</div>

# Ordenação topológica em tempo linear com DFS

```
DFS(Graph G=(V,E), vertex s)
  mark s as visited
  for each edge (s,v):
    if v is not visited
      DFS(G, v)
  f(s) = current
  current = current - 1

topological_sort(Graph G=(V,E))
  global current = |V|
  mark all nodes not visited
  for v in V:
    if v is not visited:
      DFS(G, v)
```

## Corretude

<strong><p class="lemma">A função $f$ obtida é uma bijeção de $V$ em $\{1, \dotsc, |V|\}$ </p></strong>
<em>Prova:</em><div class="proof">
Pela corretude do algoritmo de DFS, cada vértice é visitado uma única vez: isto é, para cada $v \in V$, ocorre uma única chamada de $DFS(G, v)$ (no início da qual $v$ é marcado como visitado). Logo, $current$ é decrementado um total de $|V|$ vezes, mostrando que a imagem de $f$ é exatamente $\{1, \dotsc, |V|\}$.

</div>

<strong><p class="theorem"> $f$ é uma ordenação topológica.</p></strong>
<em>Prova:</em><div class="proof">
Seja $(u,v) \in E$ uma aresta. O lema anterior já garante que $f$ é uma bijeção. Basta, agora, provar que $f(u) < f(v)$. Temos dois casos:

<strong><h4>CASO 1: $u$ é visitado antes de $v$</h4></strong>

<div class="proof">

Então ao iterar sobre a adjacência de $u$, o algoritmo encontra $v$ ainda não visitado, e a chamada a $DFS(v)$ é posta no stack. Pela natureza LIFO (Last-In-First-Out) da recursão, temos que a chamada a $DFS(v)$ é resolvida primeiro - portanto, quando $current$ foi decrementado menos. Logo $f(u) < f(v)$.

</div>

<strong><h4>CASO 2: $u$ é visitado depois de $v$</h4>
</strong>

<div class="proof">

Como $v$ foi visitado primeiro, isso significa que a chamada recursiva a $DFS(v)$ foi iniciada primeiro. Essa chamada <strong>não pode ter encontrado $u$</strong>, pois isso implicaria que existe um caminho $v \to u$, o que, juntando com a aresta $(u,v)$, formaria um ciclo.

Logo, a chamada a $DFS(v)$ foi finalizado (e retirada da stack) antes mesmo da chamada a $DFS(u)$ ter começado, e com isso o valor de $current$ era mais alto ao finalizar a busca em profundidade partindo de $v$ do que partindo de $u$. Em outras palavras, $f(u) < f(v)$.

</div>

Em qualquer caso, essa afirmação, junto à anterior, mostram que a função $f$ produzida é uma ordenação topológica da DAG $G$.

</div>

### Complexidade

<strong><p class="theorem"> A complexidade do algoritmo de ordenação topológica é $O(|V| + |E|)$ , o mesmo da DFS.

</p></strong>

<em>Prova:</em><div class="proof">
Como as operações acrescentadas a cada iteração são $O(1)$, segue que a complexidade é a mesma da DFS normal (tomada a partir de cada vértice), a qual já provamos que é $O(|V| + |E|)$.

</div>
