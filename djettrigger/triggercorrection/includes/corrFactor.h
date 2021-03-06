#ifndef CORRFACTOR_
#define CORRFACTOR_

#include <vector>

// float_t ptDcorrBins[] = {4, 999};
// std::vector<std::vector<Float_t>>corrFactor_pp = {{1.23604, 1.05675, 0.788659, 0.811985},
//                                                   {1.02654, 0.860472, 0.674958, 0.631921}};
// std::vector<std::vector<Float_t>>corrFactor_PbPb = {{0.965352, 0.95916, 1.12075, 0.862204},
//                                                     {1.08946, 0.806888, 0.988274, 0.821714}};
// std::vector<std::vector<Float_t>>corrFactorSg_pp = {{1.17866, 0.985846, 0.922587, 0.858075},
//                                                     {1.00212, 1.00018, 0.932779, 0.928736}};
// std::vector<std::vector<Float_t>>corrFactorSg_PbPb = {{1.18805, 1.16653, 0.837553, 0.696144},
//                                                       {0.759497, 2.8585, 1.73271, 0.921465}};

std::vector<std::vector<Float_t>>corrFactor6080_pp = {{1.13526, 0.861353, 0.758731, 0.739018}};
std::vector<std::vector<Float_t>>corrFactor80100_pp = {{1.13437, 0.8797, 0.789466, 0.758}};
std::vector<std::vector<Float_t>>corrFactor100999_pp = {{1.13211, 0.876474, 0.82262, 0.859951}};
std::vector<std::vector<Float_t>>corrFactor60999_pp = {{1.17343, 1.01488, 0.951858, 0.923028},
                                                       {1.05196, 0.825363, 0.694105, 0.739121}};
std::vector<std::vector<Float_t>>corrFactor6080_PbPb = {{1.10552, 0.893129, 0.900363, 0.849218}};
std::vector<std::vector<Float_t>>corrFactor80100_PbPb = {{1.11873, 0.971808, 0.715702, 0.992708}};
std::vector<std::vector<Float_t>>corrFactor100999_PbPb = {{1.29016, 0.706269, 0.68846, 0.741864}};
std::vector<std::vector<Float_t>>corrFactor60999_PbPb = {{0.872042, 0.940332, 1.07469, 1.05322},
                                                         {1.05789, 0.880384, 0.764462, 1.2871}};

std::vector<std::vector<Float_t>>corrFactorSg6080_pp = {{1.0114, 1.01135, 0.965177, 0.956598}};
std::vector<std::vector<Float_t>>corrFactorSg80100_pp = {{0.999431, 1.019, 0.983467, 1.00556}};
std::vector<std::vector<Float_t>>corrFactorSg100999_pp = {{0.998578, 1.0133, 0.995262, 0.991134}};
std::vector<std::vector<Float_t>>corrFactorSg60999_pp = {{1.11551, 1.03504, 0.960894, 0.951966},
                                                         {1.00967, 0.982058, 0.914683, 0.921759}};
std::vector<std::vector<Float_t>>corrFactorSg6080_PbPb = {{0.837279, 1.54263, 1.03652, 0.994842}};
std::vector<std::vector<Float_t>>corrFactorSg80100_PbPb = {{0.894661, 1.33485, 1.0368, 0.927311}};
std::vector<std::vector<Float_t>>corrFactorSg100999_PbPb = {{0.915823, 1.24216, 1.0335, 0.958818}};
std::vector<std::vector<Float_t>>corrFactorSg60999_PbPb = {{1.15877, 1.08516, 0.938007, 0.888238},
                                                           {0.86295, 1.78793, 1.03848, 0.842844}};

// float_t ptDcorrBins[] = {4, 10, 15, 20, 25, 30, 40, 60, 999};
// std::vector<std::vector<Float_t>> corrFactor_pp = {{1.00115, 1.18813, 0.953238, 0.984734},
//                                                    {1.09912, 1.04933, 0.887548, 0.900883},
//                                                    {1.12251, 0.956975, 0.632467, 0.692796},
//                                                    {1.07482, 0.812317, 0.613584, 0.55802},
//                                                    {1.03838, 0.771352, 0.584533, 0.526535},
//                                                    {1.01245, 0.837099, 0.742338, 0.742338},
//                                                    {1.00595, 0.863565, 0.875138, 0.877478},
//                                                    {1.00324, 0.918034, 0.713297, 0.942832}};
// std::vector<std::vector<Float_t>> corrFactor_PbPb = {{0.877013, 0.930327, 1.04768, 0.987328},
//                                                      {0.852287, 0.927216, 1.29123, 0.777777},
//                                                      {1.00936, 0.959375, 1.14597, 0.429269},
//                                                      {1.07863, 0.866235, 1.06115, 0.987424},
//                                                      {1.16754, 0.684527, 0.681891, 0.45225},
//                                                      {1.11442, 0.714741, 0.626912, 0.852981},
//                                                      {1.06571, 0.73991, 0.825899, 0.690033},
//                                                      {1.05112, 0.594869, 0.502406, 0.99754}};
// std::vector<std::vector<Float_t>>corrFactorSg_pp = {{1.11768, 1.06787, 1.01118, 0.910236},
//                                                     {1.18864, 1.01229, 0.888167, 0.891785},
//                                                     {1.13957, 0.898801, 0.815252, 0.79413},
//                                                     {1.06013, 0.866277, 0.795983, 0.796342},
//                                                     {1.01164, 0.938775, 0.867914, 0.897536},
//                                                     {0.994434, 1.10102, 1.0471, 0.961465},
//                                                     {0.994893, 1.13495, 1.10791, 1.11944},
//                                                     {0.998421, 1.04841, 0.98722, 1.05494}};
// std::vector<std::vector<Float_t>>corrFactorSg_PbPb = {{1.31735, 1.06232, 1.01463, 0.860436},
//                                                       {1.20514, 1.17321, 0.771123, 0.619775},
//                                                       {1.02892, 1.10773, 0.759348, 0.46839},
//                                                       {0.822813, 1.51409, 1.0676, 0.643133},
//                                                       {0.755852, 2.80613, 1.79824, 0.802019},
//                                                       {0.759507, 5.6401, 2.80097, 1.2381},
//                                                       {0.820857, 7.83332, 3.2549, 1.3279},
//                                                       {0.911254, 4.68959, 1.57825, 1.07348}};

#endif
