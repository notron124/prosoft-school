#include <string>
#include <iostream>
#include <stdbool.h>
#include <fstream>
#include <filesystem>
#include <queue>
#include "roller_coaster.h"

inline const int CAPACITY_INDEX = 0;
inline const int RIDES_INDEX = 1;

typedef enum test_state_t {
   PASSED = 0,
   FAILED,
} test_state_t;

test_state_t simple_case() {
   std::ifstream input_data("../../tests/datasets/1.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/1_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

test_state_t thousand_groups_of_a_few_people() {
   std::ifstream input_data("../../tests/datasets/2.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/2_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

test_state_t same_groups_several_times() {
   std::ifstream input_data("../../tests/datasets/3.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/3_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

test_state_t all_at_once() {
   std::ifstream input_data("../../tests/datasets/4.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/4_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

test_state_t high_earnings() {
   std::ifstream input_data("../../tests/datasets/5.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/5_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

test_state_t large_dataset() {
   std::ifstream input_data("../../tests/datasets/6.txt");

   if (!input_data.is_open()) {
      std::cerr << "Error opening the file!" << std::endl;
   }

   std::vector<int> initial_data;
   std::queue<int> coaster_queue;

   int data_cntr = 0;
   std::string input;
   while (input_data >> input) {
      if (data_cntr++ > 2) {
         coaster_queue.push(std::stoi(input));
      } else {
         initial_data.push_back(std::stoi(input));
      }
   }
   input_data.close();

   input_data.open("../../tests/datasets/6_answer.txt");

   input_data >> input;

   std::cout << input;

   long long expexted = std::stoll(input); 
   long long got = calculate_earnings(coaster_queue, initial_data[CAPACITY_INDEX], initial_data[RIDES_INDEX]);

   std::cout << "[TEST] simple_case: " << std::endl;
   if (got == expexted) {
      std::cout << "PASSED" << std::endl;
      return PASSED;
   }

   std::cout << "FAILED" << std::endl;
   std::cout << "Got: " << got << "Expected: " << expexted << std::endl;

   return FAILED;
}

// Можно было запустить все тесты разом через for так как единственное различие, это название файлов, но хотелось сохранинть их разделение
int main(int argc, char* argv[]) {
   if (argc < 2) {
      printf("[ERROR] Missing test name.\n");
      printf("Usage: %s test_name\n", argv[0]);
      return 1;
   }

   std::string test_name = argv[1];
   test_state_t result = FAILED;

   if (test_name.find("simple_case") != std::string::npos) {
      result = simple_case();
   } else if (test_name.find("thousand_groups_of_a_few_people") != std::string::npos) {
      result = thousand_groups_of_a_few_people();
   } else if (test_name.find("same_groups_several_times") != std::string::npos) {
      result = same_groups_several_times();
   } else if (test_name.find("all_at_once") != std::string::npos) {
      result = all_at_once();
   } else if (test_name.find("high_earnings") != std::string::npos) {
      result = high_earnings();
   } else if (test_name.find("large_dataset") != std::string::npos) {
      result = large_dataset();
   } else {
      printf("[ERROR] Unknown test '%s'\n", test_name);
      return 1;
   }

   return (result == PASSED) ? 0 : 1;
}