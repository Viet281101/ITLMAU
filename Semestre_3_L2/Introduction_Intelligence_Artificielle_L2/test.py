import math


def _change_origin_of_point_b_to_point_a(point_a, point_b):
    # uses standard Y axis orientation, not screen orientation
    return (point_b[0] - point_a[0], point_b[1] - point_a[1])

def _calc_angle_segment_a_b_with_x_axis(point_a, point_b):
    # uses standard Y axis orientation, not screen orientation
    xa, ya = point_a
    xb, yb = _change_origin_of_point_b_to_point_a(point_a, point_b)
    return math.atan2(yb, xb)

def determine_bearing_in_degrees(point_a, point_b):
    """returns the angle in degrees that line segment [point_a, point_b)]
       makes with the horizontal X axis 
    """
    # uses standard Y axis orientation, not screen orientation
    return _calc_angle_segment_a_b_with_x_axis(point_a, point_b) * 180 / math.pi

def assign_bearing_to_compass(point_a, point_b):
    """returns the standard bearing of line segment [point_a, point_b)
    """
    # uses standard Y axis orientation, not screen orientation    
    compass = {'W' : [157.5, -157.5], 
               'SW': [-157.5, -112.5], 
               'S' : [-112.5, -67.5], 
               'SE': [-67.5, -22.5], 
               'E' : [-22.5, 22.5], 
               "NE": [22.5, 67.5], 
               'N' : [67.5, 112.5], 
               'NW': [112.5, 157.5]}

    bear = determine_bearing_in_degrees(point_a, point_b)
    for direction, interval in compass.items():
        low, high = interval
        if bear >= low and bear < high:
            return direction
    return 'W'

def _convert_to_negative_Y_axis(compass_direction):
    """flips the compass_direction horizontally
    """
    compass_conversion = {'E' : 'E', 
                          'SE': 'NE', 
                          'S' : 'N', 
                          'SW': 'NW', 
                          'W' : 'W', 
                          "NW": 'SW', 
                          'N' : 'S', 
                          'NE': 'SE'}
    return compass_conversion[compass_direction]

def get_bearings(point_a, point_b):
    return _convert_to_negative_Y_axis(assign_bearing_to_compass(point_a, point_b))


# point_a = (0, 0)
# points_b = [(1, 0), (1, 3), (1, 2), (1, 1), (2, 1), (3, 1), (0, 1)]
# print("point_a, point_b     Y_up     Y_down (in screen coordinates)")
# for point_b in points_b:
#     print(point_a, ' ', point_b, '      ', assign_bearing_to_compass(point_a, point_b), '        ', get_bearings(point_a, point_b))


point_a = (0, 0)
points_b = [(-1, 0), (-1, 3), (-1, 2), (-1, 1), (-2, 1), (-3, 1), (0, 1)]
print("point_a, point_b     Y_up     Y_down (in screen coordinates)")
for point_b in points_b:
    print(point_a, ' ', point_b, '      ', assign_bearing_to_compass(point_a, point_b), '        ', get_bearings(point_a, point_b))
