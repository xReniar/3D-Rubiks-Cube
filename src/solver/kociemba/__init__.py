from . import solve
import time

def solve_best_generator(cube_state, max_length=25, max_time=10):
    sm = solve.SolutionManager(cube_state)
    timeout = time.time() + max_time
    while True:
        solution = sm.solve(max_length, timeout)

        if(isinstance(solution, str)):
            yield solution
            max_length = len(solution.split(" ")) - 1
        elif solution == -2 or solution == -1:
            break
        else:
            raise RuntimeError(
                f"SolutionManager.solve: unexpected return value {solution}"
            )    

def main(cube_state:str):
    solutions = list(solve_best_generator(cube_state, max_length=25, max_time=10))
    solutions.sort()
    return solutions[0]