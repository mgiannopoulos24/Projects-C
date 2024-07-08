# Project Shop

For this project we have a certain amount of money available, let's say M, and we want to buy N products with it. For each product i (1 ≤ i ≤ N), there are Ki model choices available, each costing Cij (1 ≤ j ≤ Ki , Cij > 0). 

For example, suppose we have 500 euros available and we want to buy a computer, a printer and an external disk, spending as much money as we can. Let's say that for the computer we have three choices, an HP, a Dell and an Asus. For the printer we have two choices, an Epson and a Lexmark, and for the external drive we have four choices, a Seagate, a Samsung, a Maxtor and a Toshiba. For each possible model of the products we want to buy, we know the cost. 

What is the maximum amount we can spend, at most M, to buy one model of each of the N products?

This project was solved with 3 different methods.

- Recursive method (```shoprec.c```):<br>

This method solves the problem using recursive logic. We start from the products and the amount of money available. For each product, we consider all possible options and calculate the maximum amount we can spend. This is repeated recursively for each product, taking into account the amount of money available and the options for each product.

- Recursive method with memorization(```shopmem.c```):<br>

In this method, we use a memory table (or cache) to store intermediate results so that they are not recalculated. Whenever we need an intermediate result, we first check if it already exists in memory. If so, we use it directly, otherwise we compute it and store it in memory for future use.

- Iterative method with dynamic programming(```shopdp.c```): <br>

This method uses dynamic programming to solve the problem. We start from the smallest problems and gradually construct solutions for larger and larger sub-problems. We keep a table that stores the optimal solutions for each subproblem so that we do not compute the same subproblems multiple times. In this way, we arrive at an optimal solution for the original problem.

The files ```shopdpcost.c``` and ```shopmemcost.c``` also are modified so that the costs of the models to be purchased are also found, in order to spend the largest possible amount of money from the initially available amount. If there is more than one combination of model costs that leads to the optimal solution, your program only needs to print one of them. Whether or not the costs are printed depends on whether or not the symbolic constant COSTS is set. 


**Note:** This project is the 3rd assignment of Introduction to Programming 2020-21 (Κ04) course of DIT NKUA.