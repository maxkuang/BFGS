#include <math.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
void test29f02(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double tmp  = 0.0;
    double tmp2 = 1.0;
    int idx     = 0;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
        
        tmp  = fabs(x[j]);
        
        if (tmp>fval) {
            fval = tmp;
            idx  = j;
            
        }
    }
    
    if (x[idx]<0) tmp2 = -1.0;
    
    g[idx] = tmp2;
    *f     = fval;
}

void test29f05(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double fa   = 0.0;
    double tmp3 = 1.0;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
    }
    
    for (int j = 0; j<n; j++) {
        fa = 0.0;
        for (int i = 0; i<n; i++) {
            fa = fa + x[i]/( ((double)(i+j+1)) );
        }
        fval = fval + fabs(fa);
        tmp3 = 1.0;
        if (fa<0) tmp3 = -1.0;
        for (int i = 0; i<n; i++) {
            g[i] = g[i] + tmp3/( ((double)(i+j+1)) );
        }
    }
    
    *f = fval;  
    
}

void test29f06(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double tmp  = 0.0;
    double tmp2 = 0.0;
    double tmp3 = 1.0;
    int k       = 0;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
        tmp  = (3.0 - 2.0*x[j])*x[j] + 1;
        if (j>0) tmp = tmp-x[j-1];
        if (j<(n-1)) tmp = tmp-x[j+1];
        tmp2 = fabs(tmp);
        if (fval <= tmp2) {
            fval = tmp2;
            k = j;
            tmp3 = 1.0;
            if (tmp<0.0) tmp3 = -1.0;
        }
    }
    g[k] = tmp3*(3.0-4.0*x[k]);
    if (k>0) g[k-1]=-tmp3;
    if (k<(n-1)) g[k+1] = -tmp3;
    *f = fval;
}

void test29f11(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double fa   = 0.0;
    double tmp3 = 1.0;
    int i       = 0;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
    }
    
    for (int ka = 0; ka<(2*n-2); ka++) {

        i = ka/2;
        if ((ka % 2)==0) {
            fa   = x[i] + x[i+1]*((5-x[i+1])*x[i+1]-2) - 13;
            tmp3 = 1.0;
            if (fa<0) tmp3 = -1.0;
            g[i] = g[i] + tmp3;
            g[i+1] = g[i+1] + (10*x[i+1]-3*x[i+1]*x[i+1] - 2)*tmp3;
        }
        else {
            fa   = x[i] + x[i+1]*((1+x[i+1])*x[i+1]-14) - 29;
            tmp3 = 1.0;
            if (fa<0) tmp3 = -1.0;
            g[i] = g[i] + tmp3;
            g[i+1] = g[i+1] + (2*x[i+1]+3*x[i+1]*x[i+1] - 14)*tmp3;
        }
        
        fval = fval + fabs(fa);
        
    }
    
    *f = fval;
    
}

void test29f22(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double fa   = 0.0;
    double U    = 1.0/((double)n + 1.0);
    double V    = 0.0;
    double tmp  = 0.0;
    double tmp3 = 1.0;
    int k       = 1;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
    }
    
    for (int ka = 0; ka<n; ka++) {
        
        V   = ( ((double)ka)+1.0) * U;
        tmp = (x[ka]+V+1.0);
        fa  = 2*x[ka] + 0.50*U*U*tmp*tmp*tmp;
        if (ka>0) fa = fa - x[ka-1];
        if (ka<(n-1)) fa = fa - x[ka+1];
        if (fval < fabs(fa) ){
            k  = ka;
            tmp3 = 1.0;
            if (fa<0) tmp3 = -1.0;
            fval = fabs(fa);
        }
    }
    V    = ((double)k)*U;
    tmp  = (x[k]+V+1);
    g[k] = (2.0 + 1.5*U*U*tmp*tmp)*tmp3;
    if (k>0) g[k-1] = -tmp3;
    if (k<(n-1)) g[k+1] = -tmp3;
    
    *f = fval;
}

/* NOT DEBUGGED
void test29f24(double *f, double *g, double *x, int n) {
    
    double fval = 0.0;
    double fa   = 0.0;
    double tmp3 = 0.0;
    double P    = 10.0;
    double H    = 1.0/( ((double)n)+1.0 );
    int k       = 1;
    
    for (int j = 0; j<n; j++) {
        g[j] = 0.0;
    }
    
    for (int ka = 0; ka<n; ka++) {
        if (ka<1) {
            fa=2.0*x[ka]+P*H*H*sinh(P*x[ka]) - x[ka+1];
        }
        else if (ka<(n-1)) {
            fa=2.0*x[ka]+P*H*H*sinh(P*x[ka]) - x[ka+1] - x[ka-1];
        }
        else {
            fa=2.0*x[ka]+P*H*H*sinh(P*x[ka]) - x[ka-1] + 1.0;
        }
        
        if (fval<fabs(fa)) {
            k = ka;
            tmp3 = 1.0;
            if (fa<0) tmp3 = -1.0;
            fval = fabs(fa);
        }
    }
    
    g[k]   = tmp3*(2*P*P*H*H*cosh(P*x[k]));
    
    if (k<1) {
        g[k+1] = -tmp3;
    }
    else if (k<(n-1)) {
        g[k-1] = -tmp3;
        g[k+1] = -tmp3; 
    }
    else {
        g[k-1] = -tmp3;
    }
    
    *f = fval;
    
}
*/

}