# Coordinate conversion from a rectangular space to another rectangular space
## Problem definition
Assuming a source rectangle is defined to encircle mathmatical problem region.
Generalized point in the source rectangle is denoted by
$\text{P}_\text{S}$ . A canvas rectangle corresponds to the source rectangle.
Canvas points corresponding to $\text{P}_\text{S}$ is denoted by
$\text{P}_\text{C}$ . A matrix converting $\text{P}_\text{C}$ to
$\text{P}_\text{S}$ is denoted by $\text{M}$ . The relationship is represented by
$$\begin{equation}
    \text{P}_\text{C} = \text{M} \text{P}_\text{S} .
\end{equation}$$

Considering the bottom-left points and the top-right points of the source space
and the canvas space.

Bottom-left in the source space:
$$\begin{equation}
    \text{P}_\text{S0}  =  (x_\text{S0}, y_\text{S0})
\end{equation}$$

Top-right in the source space:
$$\begin{equation}
    \text{P}_\text{S1}  =  (x_\text{S1}, y_\text{S1})
\end{equation}$$

Bottom-left in the canvas space:
$$\begin{equation}
    \text{P}_\text{C0}  =  (x_\text{C0}, y_\text{C0})
\end{equation}$$

Top-right in the canvas space:
$$\begin{equation}
    \text{P}_\text{C1}  =  (x_\text{C1}, y_\text{C1})
\end{equation}$$

whole equations are

$$\begin{equation}
    \text{P}_\text{C0}  =  \text{M} \text{P}_\text{S0},
\end{equation}$$

$$\begin{equation}
    \text{P}_\text{C1}  =  \text{M} \text{P}_\text{S1} .
\end{equation}$$

$\text{M}$ is a 2D transform matrix without rotation and
the matrix is represented by
$$\begin{equation}
\text{M} = \begin{bmatrix}
    a & 0 & c \\ 0 & e & f \\ 0 & 0 & 1
\end{bmatrix}.
\end{equation}$$

## Organizing formulus
Expanding (6) and (7),
$$\begin{equation}
    x_\text{C0} = a x_\text{S0} + c
\end{equation}$$
$$\begin{equation}
    y_\text{C0} = e y_\text{S0} + f
\end{equation}$$
$$\begin{equation}
    x_\text{C1} = a x_\text{S1} + c
\end{equation}$$
$$\begin{equation}
    y_\text{C1} = e y_\text{S1} + f
\end{equation}$$
Summarizing (9) - (12),
$$\begin{equation}
    \begin{bmatrix}
        x_\text{S0} & 1 & 0 & 0 \\
        0 & 0 & y_\text{S0} & 1 \\
        x_\text{S1} & 1 & 0 & 0 \\
        0 & 0 & y_\text{S1} & 1 \\
    \end{bmatrix}
    \begin{bmatrix}
        a \\ c \\ e \\ f
    \end{bmatrix} = 
    \begin{bmatrix}
        x_\text{C0} \\ y_\text{C0} \\ x_\text{C1} \\ y_\text{C1}
    \end{bmatrix} .
\end{equation}$$
Exchanging the first column and the second column, and exchanging the third column and the fourth column,
$$\begin{equation}
    \begin{bmatrix}
        1 & x_\text{S0} & 0 & 0 \\
        0 & 0 & 1 & y_\text{S0} \\
        1 & x_\text{S1} & 0 & 0 \\
        0 & 0 & 1 & y_\text{S1} \\
    \end{bmatrix}
    \begin{bmatrix}
        c \\ a \\ f \\ e
    \end{bmatrix} =
    \begin{bmatrix}
        x_\text{C0} \\ y_\text{C0} \\ x_\text{C1} \\ y_\text{C1}
    \end{bmatrix} .
\end{equation}$$
Exchanging the second row and the third row,
$$\begin{equation}
    \begin{bmatrix}
        1 & x_\text{S0} & 0 & 0 \\
        1 & x_\text{S1} & 0 & 0 \\
        0 & 0 & 1 & y_\text{S0} \\
        0 & 0 & 1 & y_\text{S1} \\
    \end{bmatrix}
    \begin{bmatrix}
        c \\ a \\ f \\ e
    \end{bmatrix} =
    \begin{bmatrix}
        x_\text{C0} \\ x_\text{C1} \\ y_\text{C0} \\ y_\text{C1}
    \end{bmatrix} .
\end{equation}$$
Solving equation (15) to obtain $a$, $c$, $e$, and $f$,
$$\begin{equation}
    \begin{bmatrix}
        c \\ a \\ f \\ e
    \end{bmatrix} =
    \begin{bmatrix}
        1 + {x_\text{S0}\over{x_\text{S1} - x_\text{S0}}} &
        -x_\text{S0}\over{x_\text{S1} - x_\text{S0}} & 0 & 0 \\
        -1\over{x_\text{S1} - x_\text{S0}} & 1\over{x_\text{S1} - x_\text{S0}} & 0 & 0 \\
        0 & 0 & 1 + {y_\text{S0}\over{y_\text{S1} - y_\text{S0}}} &
        {-y_\text{S0}\over{y_\text{S1} - y_\text{S0}}} \\
        0 & 0 & -1\over{y_\text{S1} - y_\text{S0}} & 1\over{y_\text{S1} - y_\text{S0}}
    \end{bmatrix}
    \begin{bmatrix}
        x_\text{C0} \\ x_\text{C1} \\ y_\text{C0} \\ y_\text{C1}
    \end{bmatrix} .
\end{equation}$$
Assign the following symbols to each matrix and vectors as follows.
$$\begin{equation}
    \text{M}_\text{E} = \begin{bmatrix}c \\ a \\ f \\ e\end{bmatrix}
\end{equation}$$
$$\begin{equation}
    \text{M}_\text{S} =
    \begin{bmatrix}
        1 + {x_\text{S0}\over{x_\text{S1} - x_\text{S0}}} &
        -x_\text{S0}\over{x_\text{S1} - x_\text{S0}} & 0 & 0 \\
        -1\over{x_\text{S1} - x_\text{S0}} & 1\over{x_\text{S1} - x_\text{S0}} & 0 & 0 \\
        0 & 0 & 1 + {y_\text{S0}\over{y_\text{S1} - y_\text{S0}}} &
        {-y_\text{S0}\over{y_\text{S1} - y_\text{S0}}} \\
        0 & 0 & -1\over{y_\text{S1} - y_\text{S0}} & 1\over{y_\text{S1} - y_\text{S0}}
    \end{bmatrix}
\end{equation}$$
$$\begin{equation}
    \text{M}_\text{C} =
    \begin{bmatrix}
        x_\text{C0} \\ x_\text{C1} \\ y_\text{C0} \\ y_\text{C1}
    \end{bmatrix}
\end{equation}$$