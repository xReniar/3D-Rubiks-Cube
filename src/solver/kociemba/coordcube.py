from .tables import Tables
from .cubiecube import CubieCube


class CoordCube:
    def __init__(self, twist=0, flip=0, udslice=0, edge4=0, edge8=0, corner=0):
        self.tables = Tables()

        # initialise from cubiecube c
        self.twist = twist
        self.flip = flip
        self.udslice = udslice
        self.edge4 = edge4
        self.edge8 = edge8
        self.corner = corner

    @classmethod
    def from_cubiecube(cls, cube):
        if not isinstance(cube, CubieCube):
            raise TypeError("Expected argument of type CubieCube")
        return cls(
            cube.twist,
            cube.flip,
            cube.udslice,
            cube.edge4,
            cube.edge8,
            cube.corner,
        )

    def move(self, mv):
        self.twist = self.tables.twist_move[self.twist][mv]
        self.flip = self.tables.flip_move[self.flip][mv]
        self.udslice = self.tables.udslice_move[self.udslice][mv]
        self.edge4 = self.tables.edge4_move[self.edge4][mv]
        self.edge8 = self.tables.edge8_move[self.edge8][mv]
        self.corner = self.tables.corner_move[self.corner][mv]
