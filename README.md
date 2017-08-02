Diversity-L2R
=============
A simple formulation and its implementation to get the best top k documents given a query, considering precision and diversity as variables.


Given a set of documents **D** and a set of queries **Q** the goal of Learning to Rank (L2R) is to learn a model that ranks **D** and any other documents, given any other query. In the "classic" version, we're just concerned with precision. But here we added another variable, diversity.<br><br>
So, we try to optimize the F score between precision and diversity. Diversity defined as the number of different types found among the top k ranked documents.<br><br>
The precision of each document can be forecasted using any L2R model; one can use methods like Random Forest, SVM, LambdaMART, etc. And the types of each document can be defined using any method you want.<br><br><br>


Expected Input
-------------

Three integers: **n**, **m** and **k**.<br>
**n** representing the number of documents.<br>
**m** representing the number of types of documents.<br>
**k** representing the number of documents that will be selected.<br><br>
**n** lines follows:<br>
For each line there is a real number **p**, the precision of the i-th document.<br><br>
Another **n** lines follows:<br>
For each line there is an integer **x**, the number of types assigned to the i-th document.<br>
The integer **x** is followed by **x** other integers, the types of the document.<br>

Everything here is 0-based.<br><br>


Input Example:<br>
5 3 2<br>
0.1<br>
0.5<br>
0.7<br>
0.9<br>
0.3<br>
1 1<br>
3 0 1 2<br>
2 1 2<br>
0<br>
1 0<br>
