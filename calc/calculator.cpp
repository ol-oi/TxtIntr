#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

void printUsage() {
    std::cout << "Использование: calculator -o <operation> <operand1> <operand2> ... <operandN>\n";
    std::cout << "Поддерживаемые операции:\n";
    std::cout << "  -o multiply (умножение)\n";
    std::cout << "  -o divide (деление первого операнда на все остальные)\n";
}

double multiply(const std::vector<double>& operands) {
    double result = 1.0;
    for (double operand : operands) {
        result *= operand;
    }
    return result;
}

double divide(const std::vector<double>& operands) {
    double result = operands[0];
    for (size_t i = 1; i < operands.size(); ++i) {
        if (operands[i] == 0) {
            std::cerr << "Ошибка: деление на ноль!" << std::endl;
            exit(EXIT_FAILURE);
        }
        result /= operands[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        printUsage();
        return 1;
    }

    std::string operation;
    std::vector<double> operands;

    // Обработка параметров командной строки
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                printUsage();
                return 1;
            }
        } else {
            try {
                double operand = std::stod(argv[i]);
                operands.push_back(operand);
            } catch (const std::invalid_argument&) {
                std::cerr << "Ошибка: недопустимый операнд '" << argv[i] << "'." << std::endl;
                return 1;
            }
        }
    }

    // Проверка количества операндов
    if (operands.size() < 5 || operands.size() > 7) {
        std::cerr << "Ошибка: количество операндов должно быть от 5 до 7." << std::endl;
        return 1;
    }

    // Выполнение операции
    double result = 0.0;
    if (operation == "multiply") {
        result = multiply(operands);
        std::cout << "Результат умножения: " << result << std::endl;
    } else if (operation == "divide") {
        result = divide(operands);
        std::cout << "Результат деления: " << result << std::endl;
    } else {
        std::cerr << "Ошибка: неподдерживаемая операция '" << operation << "'." << std::endl;
        return 1;
    }

    return 0;
}
