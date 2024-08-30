import time

from .coordcube import CoordCube
from .facecube import FaceCube
from .pieces import Color
from .tables import Tables


class SolutionManager:
    def __init__(self, facelets:str):
        self.tables = Tables()

        self.facelets = facelets.upper()

    def solve(self):
        # defining parameters
        max_length=25
        timeout=float("inf")

        # prepare for phase 1
        self._phase_1_initialise(max_length)
        self._allowed_length = max_length
        self._timeout = timeout

        for depth in range(self._allowed_length):
            n = self._phase_1_search(0, depth)
            if n >= 0:
                # solution found
                return self._solution_to_string(n)
            elif n == -2:
                # time limit exceeded
                return -2

        # no solution found
        return -1

    def _phase_1_initialise(self, max_length):
        self.axis = [0] * max_length
        self.power = [0] * max_length

        self.twist = [0] * max_length
        self.flip = [0] * max_length
        self.udslice = [0] * max_length

        self.corner = [0] * max_length
        self.edge4 = [0] * max_length
        self.edge8 = [0] * max_length

        self.min_dist_1 = [0] * max_length
        self.min_dist_2 = [0] * max_length

        self.f = FaceCube(self.facelets)
        self.c = CoordCube.from_cubiecube(self.f.to_cubiecube())
        self.twist[0] = self.c.twist
        self.flip[0] = self.c.flip
        self.udslice[0] = self.c.udslice
        self.corner[0] = self.c.corner
        self.edge4[0] = self.c.edge4
        self.edge8[0] = self.c.edge8
        self.min_dist_1[0] = self._phase_1_cost(0)

    def _phase_2_initialise(self, n):
        if time.time() > self._timeout:
            return -2
        # initialise phase 2 search from the phase 1 solution
        cc = self.f.to_cubiecube()
        for i in range(n):
            for j in range(self.power[i]):
                cc.move(self.axis[i])
        self.edge4[n] = cc.edge4
        self.edge8[n] = cc.edge8
        self.corner[n] = cc.corner
        self.min_dist_2[n] = self._phase_2_cost(n)
        for depth in range(self._allowed_length - n):
            m = self._phase_2_search(n, depth)
            if m >= 0:
                return m
        return -1

    def _phase_1_cost(self, n):
        return max(
            self.tables.udslice_twist_prune[self.udslice[n], self.twist[n]],
            self.tables.udslice_flip_prune[self.udslice[n], self.flip[n]],
        )

    def _phase_2_cost(self, n):
        return max(
            self.tables.edge4_corner_prune[self.edge4[n], self.corner[n]],
            self.tables.edge4_edge8_prune[self.edge4[n], self.edge8[n]],
        )

    def _phase_1_search(self, n, depth):
        if time.time() > self._timeout:
            return -2
        elif self.min_dist_1[n] == 0:
            return self._phase_2_initialise(n)
        elif self.min_dist_1[n] <= depth:
            for i in range(6):
                if n > 0 and self.axis[n - 1] in (i, i + 3):
                    continue
                for j in range(1, 4):
                    self.axis[n] = i
                    self.power[n] = j
                    mv = 3 * i + j - 1

                    # update coordinates
                    self.twist[n + 1] = self.tables.twist_move[self.twist[n]][
                        mv
                    ]
                    self.flip[n + 1] = self.tables.flip_move[self.flip[n]][mv]
                    self.udslice[n + 1] = self.tables.udslice_move[
                        self.udslice[n]
                    ][mv]
                    self.min_dist_1[n + 1] = self._phase_1_cost(n + 1)

                    # start search from next node
                    m = self._phase_1_search(n + 1, depth - 1)
                    if m >= 0:
                        return m
                    if m == -2:
                        # time limit exceeded
                        return -2
        # if no solution found at current depth, return -1
        return -1

    def _phase_2_search(self, n, depth):
        if self.min_dist_2[n] == 0:
            return n
        elif self.min_dist_2[n] <= depth:
            for i in range(6):
                if n > 0 and self.axis[n - 1] in (i, i + 3):
                    continue
                for j in range(1, 4):
                    if i in [1, 2, 4, 5] and j != 2:
                        continue
                    self.axis[n] = i
                    self.power[n] = j
                    mv = 3 * i + j - 1

                    # update coordinates following the move mv
                    self.edge4[n + 1] = self.tables.edge4_move[self.edge4[n]][
                        mv
                    ]
                    self.edge8[n + 1] = self.tables.edge8_move[self.edge8[n]][
                        mv
                    ]
                    self.corner[n + 1] = self.tables.corner_move[
                        self.corner[n]
                    ][mv]
                    self.min_dist_2[n + 1] = self._phase_2_cost(n + 1)

                    # start search from new node
                    m = self._phase_2_search(n + 1, depth - 1)
                    if m >= 0:
                        return m
        return -1

    def _solution_to_string(self, length):
        def recover_move(axis_power):
            axis, power = axis_power
            if power == 1:
                return Color(axis).name
            if power == 2:
                return Color(axis).name + "2"
            if power == 3:
                return Color(axis).name + "'"
            raise RuntimeError("Invalid move in solution.")

        solution = map(
            recover_move, zip(self.axis[:length], self.power[:length])
        )
        return " ".join(solution)