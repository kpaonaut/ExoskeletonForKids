    // n--; // x_0, x_1, ..., x_n-1, n-1 pieces of splines in total
    // float l[n+1], u[n+1], z[n+1]; // a, b, c, d are class members, alr defined
    // int h[n+1];

    // l[0] = 1;
    // u[0] = 0;
    // z[0] = 0;
    // h[0] = x[1] - x[0];

    // for (int i = 1; i < n; i++) {
    //     h[i] = x[i+1] - x[i];
    //     l[i] = 2.0 * (x[i+1] - x[i-1]) - h[i-1] * u[i-1];
    //     u[i] = h[i] / l[i];
    //     a[i] = 3.0 / h[i] * (y[i+1] - y[i]) - 3.0 / h[i-1] * (y[i] - y[i-1]);
    //     z[i] = (a[i] - h[i-1] * z[i-1]) / l[i];
    // }

    // l[n] = 1.0;
    // z[n] = c[n] = 0;

    // for (int j = n-1; j >= 0; j--) {
    //     c[j] = z[j] - u[j] * c[j+1];
    //     b[j] = (y[j+1] - y[j]) / h[j] - (h[j] * (c[j+1] + 2 * c[j])) / 3.0;
    //     d[j] = (c[j+1] - c[j]) / (3.0 * h[j]);
    // }
    // for (int i = 0; i < n; i++) a[i] = y[i];
    // printf("%d %d %d %d\n", x[0], x[1], x[2], x[3]);//debug
    // printf("%f %f %f %f\n", y[0], y[1], y[2], y[3]);//debug
    // cout<<d[0]<<" "<<c[0]<<" "<<b[0]<<" "<<a[0]<<endl;
    // cout<<d[1]<<" "<<c[1]<<" "<<b[1]<<" "<<a[1]<<endl;
    // cout<<d[2]<<" "<<c[2]<<" "<<b[2]<<" "<<a[2]<<endl;
    // n++; // won't let this function mess n up. n still means number of critical pts
