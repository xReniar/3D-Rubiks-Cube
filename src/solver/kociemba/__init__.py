from . import solve

def main(cube_state:str):
    sm = solve.SolutionManager(cube_state)
    return sm.solve()