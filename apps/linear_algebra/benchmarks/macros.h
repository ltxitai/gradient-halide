#define time_it(code)                               \
    double elapsed = 0;                             \
    for (int iters = 20; ; iters *= 2) {            \
        double start = current_time();              \
        for (int i = 0; i < iters; i++) {           \
            code;                                   \
        }                                           \
        double end = current_time();                \
        elapsed = 1000 * (end - start);             \
        if (elapsed > 100000) {                     \
            elapsed /= iters;                       \
            break;                                  \
        }                                           \
    }

#define L1BytesUsed(N) 2 * N * sizeof(Scalar)
#define L1Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        Vector x(random_vector(N));                                     \
        Vector y(random_vector(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
                  << std::setw(15) << type << #benchmark                \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << 1000 * L1BytesUsed(N) / elapsed   \
                  << std::endl;                                         \
    }

#define L2BytesUsed(N) (2 + N) * N * sizeof(Scalar)
#define L2Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        Scalar beta = random_scalar();                                  \
        Vector x(random_vector(N));                                     \
        Vector y(random_vector(N));                                     \
        Matrix A(random_matrix(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
        << std::setw(15) << type << #benchmark                          \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << 1000 * L2BytesUsed(N) / elapsed   \
                  << std::endl;                                         \
    }

#define L3BytesUsed(N) 3 * N * N * sizeof(Scalar)
#define L3Benchmark(benchmark, type, code)                              \
    virtual void bench_##benchmark(int N) {                             \
        Scalar alpha = random_scalar();                                 \
        Scalar beta = random_scalar();                                  \
        Matrix A(random_matrix(N));                                     \
        Matrix B(random_matrix(N));                                     \
        Matrix C(random_matrix(N));                                     \
                                                                        \
        time_it(code)                                                   \
                                                                        \
        std::cout << std::setw(8) << name                               \
                  << std::setw(15) << type << #benchmark                \
                  << std::setw(8) << std::to_string(N)                  \
                  << std::setw(20) << std::to_string(elapsed)           \
                  << std::setw(20) << 1000 * L3BytesUsed(N) / elapsed   \
                  << std::endl;                                         \
    }
