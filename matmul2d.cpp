//------------------------------------------------------------------------------
//
//  PROGRAMA: Driver de multiplicação de matriz
//
//  PROPOSITO: Varias formas de calcular um produto da matriz:
//
//                C  = A * B
//
//           A e B são definidas para matrizes constantes para que possamos fazer um teste rápido da multiplicação.
//
//  USO: São matrizes constantes, quadradas e a ordem é definida como uma constante, ORDER (see mult.h).
//------------------------------------------------------------------------------

#include "matmul.hpp"
#include "matrix_lib.hpp"
#include "matrix_lib.cpp"
#include "util.hpp"
#include "err_code.h"
#include "device_picker.hpp"

int main(int argc, char* argv[])
{

    int N;   // A[N][N], B[N][N], C[N][N]
    int size;      // Number of elements in each matrix

    double start_time;      // Starting time
    double run_time;        // Timing data
    util::Timer timer;      // timing

    N = ORDER;

    size = N * N;

    std::vector<float> h_A(size); // Host memory for Matrix A
    std::vector<float> h_B(size); // Host memory for Matrix B
    std::vector<float> h_C(size); // Host memory for Matrix C

    cl::Buffer d_a, d_b, d_c;   // Matrices in device memory

//--------------------------------------------------------------------------------
// Criando um contexto e uma fila
//--------------------------------------------------------------------------------

    try
    {
        cl_uint deviceIndex = 0;
        parseArguments(argc, argv, &deviceIndex);

        // Get list of devices
        std::vector<cl::Device> devices;
        unsigned numDevices = getDeviceList(devices);

        // Check device index in range
        if (deviceIndex >= numDevices)
        {
            std::cout << "Invalid device index (try '--list')\n";
            return EXIT_FAILURE;
        }

        cl::Device device = devices[deviceIndex];

        std::string name;
        getDeviceName(device, name);
        std::cout << "\nUsing OpenCL device: " << name << "\n";

        std::vector<cl::Device> chosen_device;
        chosen_device.push_back(device);
        cl::Context context(chosen_device);
        cl::CommandQueue queue(context, device);

        //--------------------------------------------------------------------------------
        // Configurar os buffers, inicializar as matrizes e escreve-las na memória global
        //--------------------------------------------------------------------------------

                //  Reseta matrizes A, B e C matrices (apenas por segurança)
        initmat(N, h_A, h_B, h_C);

        d_a = cl::Buffer(context, h_A.begin(), h_A.end(), true);
        d_b = cl::Buffer(context, h_B.begin(), h_B.end(), true);
        d_c = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * size);

        //--------------------------------------------------------------------------------
        // OpenCL matrix multiplication ... Naive
        //--------------------------------------------------------------------------------

                // Cria o programa a partir do buffer de origem
        cl::Program program(context, util::loadProgram("kernels/C_elem.cl"), true);

        // Crie o kernel do programa
        cl::make_kernel<int, cl::Buffer, cl::Buffer, cl::Buffer> naive_mmul(program, "mmul");

        printf("\n===== OpenCL, matrix mult, C(i,j) per work item, order %d ======\n", N);

        // Contador de multiplicação
        for (int i = 0; i < COUNT; i++)
        {
            zero_mat(N, h_C);

            start_time = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0;

           //Execute o kernel sobre toda a gama de elementos de matriz C ... 
           //Calculando um produto de ponto para cada elemento da matriz do produto.  
           //O tamanho local está definido como NULL ... 
           //Direciono ao opencl em tempo de execução para calcular o tamanho da matriz.
            cl::NDRange global(N, N);
            naive_mmul(cl::EnqueueArgs(queue, global),
                N, d_a, d_b, d_c);

            queue.finish();

            run_time = static_cast<double>(timer.getTimeMilliseconds()) / 1000.0 - start_time;

            cl::copy(queue, d_c, h_C.begin(), h_C.end());

            results(N, h_C, run_time);

        } // fim do loop

    }
    catch (cl::Error err)
    {
        std::cout << "Exception\n";
        std::cerr << "ERROR: "
            << err.what()
            << "("
            << err_code(err.err())
            << ")"
            << std::endl;
    }

    return EXIT_SUCCESS;
}
