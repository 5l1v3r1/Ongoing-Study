// 2018-04-22T14:07+08:00
// Calculate ∫1/xdx in domain [1,2]

#include <stdio.h>

#include <gsl/gsl_integration.h>


double rational_func_x_1(double x, void *params)
{
    return 1.0 / x;
}

int main()
{
    gsl_function func = { &rational_func_x_1 };

    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(1000);

    double result;
    double error;

    if (gsl_integration_qags(&func, 1.0, 2.0, 0.0, 1e-7, 1000, workspace,
        &result, &error) == 0)
    {
        printf("Result          = %.18f\n", result);
        printf("Estimated error = %.18f\n", error);
        printf("Intervals       = %zu\n", workspace->size);
    }

    gsl_integration_workspace_free(workspace);

    return 0;
}


// References:
// Calculus, 7ed, James.Stewart, P531
// https://stackoverflow.com/questions/16512817/numerical-integration-in-c
