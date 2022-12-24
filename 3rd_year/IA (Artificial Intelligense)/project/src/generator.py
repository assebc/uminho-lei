import noise as n
import random

class Map:
    
    def __init__(self):
        ''' Constructor of class Generator
        '''
        self.map = []               # value matrix
        self.txt_map = []           # char matrix
        self.h = 0                  # map height value
        self.w = 0                  # map width value
        
        ### choking values ###
        self.wall_value = 2
        self.path_value = 3
        self.wall_chokervalue = 0.085

    def setHeight(self, value):
        '''
        Sets the map height to given value

        Parameters:
        value (int): Value to set in height
        '''
        self.h = value

    def setWidth(self, value):
        '''
        Sets the map width to given value

        Parameters:
        value (int): Value to set in height
        '''
        self.w = value

    def getWidth(self):
        '''Return the current map width
        '''
        return self.w

    def get_type(self, value):
        '''
        Get the character representation of a given value

        Parameters:
        value (int): Value of component type

        Returns:
        Char that identifies given type
        '''
        if value == self.wall_value:  # value choker
            return 'X'
        else:
            return '-'

    def get_value(self, value):
        '''
        Get the strict value representation of a given value.
        This function is useful so the value matrix has even and predefined values for walls and the path
        '''
        if value > self.wall_chokervalue:  # value choker
            return self.wall_value
        else:
            return self.path_value

    def clean(self):
        '''Cleans matrix
        '''
        self.map = []
        self.txt_map = []

    def convert_to_txt(self):
        '''Translate the current map into it's text representation
        '''
        map_lines = []
        
        for l in self.map:
            row = []
            for r in l:
                row.append(self.get_type(r))
                row.append(' ')
            row.append('\n')
            map_lines.append(row)
        
        self.txt_map = map_lines
        return self.txt_map

    def add_border(self):
        '''Adds top and bottom borders
        '''
        row = []
        for x in range(self.w):
            row.append(self.wall_value)
        self.map.append(row)

    def create(self, freqx, freqy, elevation):
        '''#### Create a random numeric value map given x and y frequency and elevation.

            This algorithm is based on a smooth value transition between random values, so called "smooth noise".
            It populates a list of lists (the map matrix) with those values.

            * Frequency X and Y influence the number of oscillations between disparate values.
              Higher frequencies produce denser maps (unwanted result in our case).
            * Elevation affects values in order to create greater contrast.
              High values tend to get even higher, influencing the surrounding values.
              This effect helps to shrink structures that are not part of the path, suitable for lower resolution maps,
              and to avoid inaccessible "holes".
            * Alongside the smooth noise generation, the current method also defines the map borders with "extreme" values.
        '''
        self.clean()    # cleans both value and text map data structures
        r = random.random()
        r2 = random.random()
        fx = freqx * r
        fy = freqy * r

        self.add_border()           # top border
        for l in range(self.h-2):   # height-2 since borders are part of the map
            row = []                # creating the array to append the row
            row.append(self.wall_value)           # left side border
            for c in range(self.w-2):  # width-2 since borders are part of the map
                nx = c/self.w - 0.5 * r2
                ny = l/self.h - 0.5 * r
                value = pow(n.snoise2(fx*nx, fy*ny), elevation)
                # appending the current position value to the row
                row.append(self.get_value(value))
            row.append(self.wall_value)           # right side border
            self.map.append(row)    # appending the current row to the map
        self.add_border()           # bottom border
    
    def generate(self,width,height):
        '''
        Generates a numeric value map with given width and height and converts it into text
        '''
        self.setHeight(height)
        self.setWidth(width)
        self.create(3,3,2)
        self.convert_to_txt()
        return self.txt_map
