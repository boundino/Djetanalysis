#ifndef CORRFACTOR_
#define CORRFACTOR_

#include <vector>

// ! jet eta 0-1.6, Dpt weight (2018.4.25)

std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.12726, 1.01301, 0.939069, 0.936218},
                                                        {1.04431, 0.856598, 0.698588, 0.693275}};
std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{1.09225, 1.00545, 0.962837, 0.950475},
                                                          {1.00769, 0.983958, 0.929715, 0.946028}};
std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.06178, 0.968375, 0.992791, 1.01106},
                                                          {1.0625, 0.821727, 0.698714, 0.685159}};
std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.08077, 1.0529, 0.941354, 0.891346},
                                                            {0.881896, 1.91261, 1.17996, 0.974245}};

std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.09689, 0.880167, 0.741043, 0.739134}};
std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{1.00244, 1.00302, 0.986969, 0.986772}};
std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.09993, 0.860205, 0.796501, 0.78924}};
std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.00622, 1.00591, 0.973502, 0.966424}};
std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.10337, 0.870652, 0.823609, 0.842393}};
std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{1.00088, 1.00968, 0.989034, 0.993169}};
std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.09674, 0.863445, 0.730943, 0.702737}};
std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{0.843418, 1.77854, 1.20402, 1.09631}};
std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.10717, 0.803746, 0.664185, 0.703006}};
std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{0.890246, 1.63129, 1.09176, 1.0509}};
std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.14457, 0.67986, 0.635053, 0.705076}};
std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{0.922639, 1.385, 1.06361, 1.02305}};

// ! jet eta 0.3-1.6
// std::vector<std::vector<Float_t>> corrFactor60999_pp = {{1.15332, 1.00313, 0.944529, 0.913613},
//                                                         {1.04719, 0.844928, 0.691269, 0.684452}};
// std::vector<std::vector<Float_t>> corrFactor60999_PbPb = {{1.07022, 0.968591, 0.990932, 0.99121},
//                                                           {1.07866, 0.829344, 0.704708, 0.68494}};
// std::vector<std::vector<Float_t>> corrFactor6080_pp = {{1.11595, 0.867601, 0.755132, 0.718664}};
// std::vector<std::vector<Float_t>> corrFactor80100_pp = {{1.1204, 0.872541, 0.779175, 0.784418}};
// std::vector<std::vector<Float_t>> corrFactor100999_pp = {{1.12354, 0.868897, 0.816446, 0.845841}};
// std::vector<std::vector<Float_t>> corrFactor6080_PbPb = {{1.16282, 0.863605, 0.735227, 0.695213}};
// std::vector<std::vector<Float_t>> corrFactor80100_PbPb = {{1.19543, 0.81764, 0.700679, 0.736634}};
// std::vector<std::vector<Float_t>> corrFactor100999_PbPb = {{1.24026, 0.739893, 0.709131, 0.777169}};

// std::vector<std::vector<Float_t>> corrFactorSg60999_pp = {{0.999236, 1.00046, 1.00623, 1.00701},
//                                                           {0.99985, 1.00174, 0.998102, 0.997398}};
// std::vector<std::vector<Float_t>> corrFactorSg60999_PbPb = {{1.00607, 0.998326, 1.00262, 1.01198},
//                                                             {1.00612, 0.833406, 0.902184, 0.929127}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_pp = {{0.999536, 1.00187, 1.00677, 1.00156}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_pp = {{1.00122, 1.00022, 0.997523, 1.00284}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_pp = {{0.99682, 1.00257, 1.0074, 1.00776}};
// std::vector<std::vector<Float_t>> corrFactorSg6080_PbPb = {{1.01578, 0.795385, 0.894044, 0.918252}};
// std::vector<std::vector<Float_t>> corrFactorSg80100_PbPb = {{1.01884, 0.804365, 0.918885, 0.92174}};
// std::vector<std::vector<Float_t>> corrFactorSg100999_PbPb = {{1.00174, 0.877935, 0.951161, 0.966611}};

#endif
