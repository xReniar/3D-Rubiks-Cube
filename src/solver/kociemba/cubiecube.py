from functools import reduce

from .pieces import Corner, Edge
from . import facecube


def choose(n, k):
    if 0 <= k <= n:
        num = 1
        den = 1
        for i in range(1, min(k, n - k) + 1):
            num *= n
            den *= i
            n -= 1
        return num // den
    else:
        return 0

_cpU = (
    Corner.UBR,
    Corner.URF,
    Corner.UFL,
    Corner.ULB,
    Corner.DFR,
    Corner.DLF,
    Corner.DBL,
    Corner.DRB,
)
_coU = (0, 0, 0, 0, 0, 0, 0, 0)
_epU = (
    Edge.UB,
    Edge.UR,
    Edge.UF,
    Edge.UL,
    Edge.DR,
    Edge.DF,
    Edge.DL,
    Edge.DB,
    Edge.FR,
    Edge.FL,
    Edge.BL,
    Edge.BR,
)
_eoU = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

_cpR = (
    Corner.DFR,
    Corner.UFL,
    Corner.ULB,
    Corner.URF,
    Corner.DRB,
    Corner.DLF,
    Corner.DBL,
    Corner.UBR,
)
_coR = (2, 0, 0, 1, 1, 0, 0, 2)
_epR = (
    Edge.FR,
    Edge.UF,
    Edge.UL,
    Edge.UB,
    Edge.BR,
    Edge.DF,
    Edge.DL,
    Edge.DB,
    Edge.DR,
    Edge.FL,
    Edge.BL,
    Edge.UR,
)
_eoR = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

_cpF = (
    Corner.UFL,
    Corner.DLF,
    Corner.ULB,
    Corner.UBR,
    Corner.URF,
    Corner.DFR,
    Corner.DBL,
    Corner.DRB,
)
_coF = (1, 2, 0, 0, 2, 1, 0, 0)
_epF = (
    Edge.UR,
    Edge.FL,
    Edge.UL,
    Edge.UB,
    Edge.DR,
    Edge.FR,
    Edge.DL,
    Edge.DB,
    Edge.UF,
    Edge.DF,
    Edge.BL,
    Edge.BR,
)
_eoF = (0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0)

_cpD = (
    Corner.URF,
    Corner.UFL,
    Corner.ULB,
    Corner.UBR,
    Corner.DLF,
    Corner.DBL,
    Corner.DRB,
    Corner.DFR,
)
_coD = (0, 0, 0, 0, 0, 0, 0, 0)
_epD = (
    Edge.UR,
    Edge.UF,
    Edge.UL,
    Edge.UB,
    Edge.DF,
    Edge.DL,
    Edge.DB,
    Edge.DR,
    Edge.FR,
    Edge.FL,
    Edge.BL,
    Edge.BR,
)
_eoD = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

_cpL = (
    Corner.URF,
    Corner.ULB,
    Corner.DBL,
    Corner.UBR,
    Corner.DFR,
    Corner.UFL,
    Corner.DLF,
    Corner.DRB,
)
_coL = (0, 1, 2, 0, 0, 2, 1, 0)
_epL = (
    Edge.UR,
    Edge.UF,
    Edge.BL,
    Edge.UB,
    Edge.DR,
    Edge.DF,
    Edge.FL,
    Edge.DB,
    Edge.FR,
    Edge.UL,
    Edge.DL,
    Edge.BR,
)
_eoL = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)

_cpB = (
    Corner.URF,
    Corner.UFL,
    Corner.UBR,
    Corner.DRB,
    Corner.DFR,
    Corner.DLF,
    Corner.ULB,
    Corner.DBL,
)
_coB = (0, 0, 1, 2, 0, 0, 2, 1)
_epB = (
    Edge.UR,
    Edge.UF,
    Edge.UL,
    Edge.BR,
    Edge.DR,
    Edge.DF,
    Edge.DL,
    Edge.BL,
    Edge.FR,
    Edge.FL,
    Edge.UB,
    Edge.DB,
)
_eoB = (0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1)


class CubieCube:
    def __init__(self, cp=None, co=None, ep=None, eo=None):
        if cp and co and ep and eo:
            self.cp = cp[:]
            self.co = co[:]
            self.ep = ep[:]
            self.eo = eo[:]
        else:
            # Initialise clean cube if position not given.
            self.cp = [
                Corner.URF,
                Corner.UFL,
                Corner.ULB,
                Corner.UBR,
                Corner.DFR,
                Corner.DLF,
                Corner.DBL,
                Corner.DRB,
            ]
            self.co = [0, 0, 0, 0, 0, 0, 0, 0]
            self.ep = [
                Edge.UR,
                Edge.UF,
                Edge.UL,
                Edge.UB,
                Edge.DR,
                Edge.DF,
                Edge.DL,
                Edge.DB,
                Edge.FR,
                Edge.FL,
                Edge.BL,
                Edge.BR,
            ]
            self.eo = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    def corner_multiply(self, b):
        corner_perm = [self.cp[b.cp[i]] for i in range(8)]
        corner_ori = [(self.co[b.cp[i]] + b.co[i]) % 3 for i in range(8)]
        self.co = corner_ori[:]
        self.cp = corner_perm[:]

    def edge_multiply(self, b):
        edge_perm = [self.ep[b.ep[i]] for i in range(12)]
        edge_ori = [(self.eo[b.ep[i]] + b.eo[i]) % 2 for i in range(12)]
        self.eo = edge_ori[:]
        self.ep = edge_perm[:]

    def multiply(self, b):
        self.corner_multiply(b)
        self.edge_multiply(b)

    def move(self, i):
        self.multiply(MOVE_CUBE[i])

    def inverse_cubiecube(self):
        cube = CubieCube()
        for e in range(12):
            cube.ep[self.ep[e]] = e
        for e in range(12):
            cube.eo[e] = self.eo[cube.ep[e]]
        for c in range(8):
            cube.cp[self.cp[c]] = c
        for c in range(8):
            ori = self.co[cube.cp[c]]
            cube.co[c] = (-ori) % 3
        return cube

    def to_facecube(self):
        ret = facecube.FaceCube()
        for i in range(8):
            j = self.cp[i]
            ori = self.co[i]
            for k in range(3):
                ret.f[
                    facecube.corner_facelet[i][(k + ori) % 3]
                ] = facecube.corner_color[j][k]
        for i in range(12):
            j = self.ep[i]
            ori = self.eo[i]
            for k in range(2):
                facelet_index = facecube.edge_facelet[i][(k + ori) % 2]
                ret.f[facelet_index] = facecube.edge_color[j][k]
        return ret

    @property
    def corner_parity(self):
        s = 0
        for i in range(7, 0, -1):
            for j in range(i - 1, -1, -1):
                if self.cp[j] > self.cp[i]:
                    s += 1
        return s % 2

    @property
    def edge_parity(self):
        s = 0
        for i in range(11, 0, -1):
            for j in range(i - 1, -1, -1):
                if self.ep[j] > self.ep[i]:
                    s += 1
        return s % 2

    # ----------   Phase 1 Coordinates  ---------- #
    @property
    def twist(self):
        return reduce(lambda x, y: 3 * x + y, self.co[:7])

    @twist.setter
    def twist(self, twist):
        if not 0 <= twist < 3 ** 7:
            raise ValueError(
                "{} is out of range for twist, must take values in "
                "0, ..., 2186.".format(twist)
            )
        total = 0
        for i in range(7):
            x = twist % 3
            self.co[6 - i] = x
            total += x
            twist //= 3
        self.co[7] = (-total) % 3

    @property
    def flip(self):
        return reduce(lambda x, y: 2 * x + y, self.eo[:11])

    @flip.setter
    def flip(self, flip):
        if not 0 <= flip < 2 ** 11:
            raise ValueError(
                "{} is out of range for flip, must take values in "
                "0, ..., 2047.".format(flip)
            )
        total = 0
        for i in range(11):
            x = flip % 2
            self.eo[10 - i] = x
            total += x
            flip //= 2
        self.eo[11] = (-total) % 2

    @property
    def udslice(self):
        udslice, seen = 0, 0
        for j in range(12):
            if 8 <= self.ep[j] < 12:
                seen += 1
            elif seen >= 1:
                udslice += choose(j, seen - 1)
        return udslice

    @udslice.setter
    def udslice(self, udslice):
        if not 0 <= udslice < choose(12, 4):
            raise ValueError(
                "{} is out of range for udslice, must take values in "
                "0, ..., 494.".format(udslice)
            )
        udslice_edge = [Edge.FR, Edge.FL, Edge.BL, Edge.BR]
        other_edge = [
            Edge.UR,
            Edge.UF,
            Edge.UL,
            Edge.UB,
            Edge.DR,
            Edge.DF,
            Edge.DL,
            Edge.DB,
        ]
        # invalidate edges
        for i in range(12):
            self.ep[i] = Edge.DB
        # we first position the slice edges
        seen = 3
        for j in range(11, -1, -1):
            if udslice - choose(j, seen) < 0:
                self.ep[j] = udslice_edge[seen]
                seen -= 1
            else:
                udslice -= choose(j, seen)
        # then the remaining edges
        x = 0
        for j in range(12):
            if self.ep[j] == Edge.DB:
                self.ep[j] = other_edge[x]
                x += 1

    @property
    def edge4(self):
        edge4 = self.ep[8:]
        ret = 0
        for j in range(3, 0, -1):
            s = 0
            for i in range(j):
                if edge4[i] > edge4[j]:
                    s += 1
            ret = j * (ret + s)
        return ret

    @edge4.setter
    def edge4(self, edge4):
        if not 0 <= edge4 < 24:
            raise ValueError(
                f"{edge4} is out of range for edge4, must take values in 0-23"
            )
        sliceedge = [Edge.FR, Edge.FL, Edge.BL, Edge.BR]
        coeffs = [0] * 3
        for i in range(1, 4):
            coeffs[i - 1] = edge4 % (i + 1)
            edge4 //= i + 1
        perm = [0] * 4
        for i in range(2, -1, -1):
            perm[i + 1] = sliceedge.pop(i + 1 - coeffs[i])
        perm[0] = sliceedge[0]
        self.ep[8:] = perm[:]

    @property
    def edge8(self):
        edge8 = 0
        for j in range(7, 0, -1):
            s = 0
            for i in range(j):
                if self.ep[i] > self.ep[j]:
                    s += 1
            edge8 = j * (edge8 + s)
        return edge8

    @edge8.setter
    def edge8(self, edge8):
        edges = list(range(8))
        perm = [0] * 8
        coeffs = [0] * 7
        for i in range(1, 8):
            coeffs[i - 1] = edge8 % (i + 1)
            edge8 //= i + 1
        for i in range(6, -1, -1):
            perm[i + 1] = edges.pop(i + 1 - coeffs[i])
        perm[0] = edges[0]
        self.ep[:8] = perm[:]

    @property
    def corner(self):
        c = 0
        for j in range(7, 0, -1):
            s = 0
            for i in range(j):
                if self.cp[i] > self.cp[j]:
                    s += 1
            c = j * (c + s)
        return c

    @corner.setter
    def corner(self, corn):
        corners = list(range(8))
        perm = [0] * 8
        coeffs = [0] * 7
        for i in range(1, 8):
            coeffs[i - 1] = corn % (i + 1)
            corn //= i + 1
        for i in range(6, -1, -1):
            perm[i + 1] = corners.pop(i + 1 - coeffs[i])
        perm[0] = corners[0]
        self.cp = perm[:]

    @property
    def edge(self):
        e = 0
        for j in range(11, 0, -1):
            s = 0
            for i in range(j):
                if self.ep[i] > self.ep[j]:
                    s += 1
            e = j * (e + s)
        return e

    @edge.setter
    def edge(self, edge):
        edges = list(range(12))
        perm = [0] * 12
        coeffs = [0] * 11
        for i in range(1, 12):
            coeffs[i - 1] = edge % (i + 1)
            edge //= i + 1
        for i in range(10, -1, -1):
            perm[i + 1] = edges.pop(i + 1 - coeffs[i])
        perm[0] = edges[0]
        self.ep = perm[:]


# we store the six possible clockwise 1/4 turn moves in the following array.
MOVE_CUBE = [CubieCube() for i in range(6)]

MOVE_CUBE[0].cp = _cpU
MOVE_CUBE[0].co = _coU
MOVE_CUBE[0].ep = _epU
MOVE_CUBE[0].eo = _eoU

MOVE_CUBE[1].cp = _cpR
MOVE_CUBE[1].co = _coR
MOVE_CUBE[1].ep = _epR
MOVE_CUBE[1].eo = _eoR

MOVE_CUBE[2].cp = _cpF
MOVE_CUBE[2].co = _coF
MOVE_CUBE[2].ep = _epF
MOVE_CUBE[2].eo = _eoF

MOVE_CUBE[3].cp = _cpD
MOVE_CUBE[3].co = _coD
MOVE_CUBE[3].ep = _epD
MOVE_CUBE[3].eo = _eoD

MOVE_CUBE[4].cp = _cpL
MOVE_CUBE[4].co = _coL
MOVE_CUBE[4].ep = _epL
MOVE_CUBE[4].eo = _eoL

MOVE_CUBE[5].cp = _cpB
MOVE_CUBE[5].co = _coB
MOVE_CUBE[5].ep = _epB
MOVE_CUBE[5].eo = _eoB
