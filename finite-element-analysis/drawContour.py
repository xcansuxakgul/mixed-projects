import numpy as np
import matplotlib.pyplot as plt
from sympy import symbols, Eq, solve

def calculate_coef_i(x,x1):
    a_i, b_i = symbols('a_i b_i')
    eq1 = Eq(a_i + b_i * x1, 0)
    eq2 = Eq(a_i + b_i * x, 1)
    sol = solve((eq1, eq2), (a_i, b_i))
    return [sol[a_i],sol[b_i]]

def findPhi_i(x,x_nodes,u_values):
    phi_sum = np.zeros_like(x)
    for i in range(len(x_nodes)):
        phi_i = np.zeros_like(x)
        phi_i2 = np.zeros_like(x)   
        if i == 0:
            # For the first node, calculate coefficients and apply mask
            mask = np.logical_and(x_nodes[i] <= x, x < x_nodes[i + 1])
            coef = calculate_coef_i(nodes[i],nodes[i+1])
            phi_i[mask] = coef[0] + coef[1] * x[mask]
        elif i == (len(x_nodes)-1):
            # For the last node, calculate coefficients and apply mask
            mask = np.logical_and(x_nodes[i-1] < x, x <= x_nodes[i])
            coef = calculate_coef_i(nodes[i],nodes[i-1])
            phi_i[mask] = coef[0] + coef[1] * x[mask]
        else:
            # For all other nodes, calculate coefficients and apply masks
            mask = np.logical_and(x_nodes[i-1] <= x, x < x_nodes[i])
            mask2 = np.logical_and(x_nodes[i] <= x, x < x_nodes[i + 1])
            coef2 = calculate_coef_i(nodes[i],nodes[i+1])
            coef = calculate_coef_i(nodes[i],nodes[i-1])
            phi_i2[mask2] = coef2[0] + coef2[1] * x[mask2]
            phi_i[mask] = coef[0] + coef[1] * x[mask]
            phi_i += phi_i2
            
        phi_sum += u_values[i] * phi_i
    
    return phi_sum

def plot_func(x,y,label):
    plt.plot(x, y, label=label)
    plt.xlabel('x')
    plt.ylabel('Function Value')
    plt.legend()
    plt.axhline(y=0, color='black')
    for node in nodes:
        plt.axvline(x=node, color='red', linestyle=':', linewidth=0.5)  # Add vertical lines at node locations
    plt.title('Function Plot')
    plt.show()

if __name__ == "__main__":
    nodes = [0,2,4,4.5,5,5.8,8.7,9.2,9.7,11.7,12.7]
    u_values = [5.1,7.2,5.9,6.1,7.4,6.3,6.5,7.3,7,8.8,8.5]
    x = np.linspace(0, 12.7, 100) 

    u_sum = findPhi_i(x, nodes, u_values)
    plot_func(x,u_sum,r'$\sum_{i=1}^{11}u_{i}\Phi_{i}$')