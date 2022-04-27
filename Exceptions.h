#pragma once

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

using std::exception;

class Failure : public exception {};

#endif