//
// Created by weining on 12/12/20.
//

/**
 * ## Lazy-evaluation: return lambda that captures the workload

saw this in c++ stl cookbook;

instead of processing the workload, capture it in a lamdba
and return this lambda for further composition

another good lazy-eval pattern is c++20's range library
 *
 * */