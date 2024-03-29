# DFAMinimizationProject
University of Trento<br>
Academic Year 2021/2022<br>
Project for Compilers course<br>
### 📄 REPORT: [report.pdf](Report.pdf)
## Abstract
In this repository it is proposed an implementation of the Watson-Daciuk’s Deterministic Finite Automata (DFA) minimization algorithm. The algorithm functionality is based on the contents illustrated in the paper ”An efficient incremental DFA minimization algorithm” written by Bruce W. Watson and Jan Daciuk. The code has been fully written in C programming language. I assume that the DFA minimization problem is well known by the reader. **Together with the implementation code there is also a Report pdf document to better understand the context.** At the beginning of this document the attention is on the key aspects of the Watson-Daciuk’s algorithm. The purpose of the following sections is to reason about data structures used in the actual implementation, efficiency and optimization strategies that has been adopted. Then there is described how to compile the code, the structure of the input and how to read the output. In order to check the correctness of the output given by the algorithm I have also implemented the DFA minimization algorithm that we have studied during the course, referred to as Partition Refinement Algorithm. At the end of the document there are some indications about this last.

## Folder structure
- `PaperImplementation` folder contains the implementation of the Watson-Daciuk’s Deterministic Finite Automata (DFA) minimization algorithm
- `slideImplementation` folder contains the implementation of the Partition Refinement Algorithm presented by the professor during the course
