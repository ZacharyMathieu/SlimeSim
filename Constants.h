#ifndef CONSTANTS_H
#define CONSTANTS_H

// TODO fix memory leak

// Window settings
#define WINDOW_WIDTH                                1600
#define WINDOW_HEIGHT                               800

// Display settings
#define DISPLAY_PHEROMONES
#define DISPLAY_SLIME
#define DISPLAY_SLIME_SIZE                          1
#define DISPLAY_SLIME_OPACITY                       75
#define DISPLAY_SLIME_COLOR                         QColor(255, 255, 0, DISPLAY_SLIME_OPACITY)
#define DISPLAY_HIGHLIGHT_PHEROMONE_COLOR           QColor(0, 255, 0)
#define DISPLAY_INACTIVE_PHEROMONE_COLOR            QColor(255, 0, 255)
#define DISPLAY_DEFAULT_PHEROMONE_COLOR(level)      QColor(0, std::min((1 - level) * 2, 1.0) * level * 255, level * 255)

// Grid settings
#define GRID_WIDTH                                  400
#define GRID_HEIGHT                                 200
#define LOOP_GRID

// Natural pheromones settings
#define RANDOM_NATURAL_PHEROMONES_COUNT             0
#define NATURAL_PHEROMONES_STRENGTH                 PHEROMONE_MAX_LEVEL

// Environment settings
#define SLIME_COUNT                                 10000

// Slime general settings
#define SLIME_SPEED                                 0.5

// Slime wall avoidance settings
#define SLIME_AVOID_WALLS
#define SLIME_WALL_DETECTION_RANGE                  10
#define SLIME_WALL_TURN_ANGLE                       0.05

// Slime pheromones settings
#define SLIME_SEEK_PHEROMONES
#define SLIME_SEEK_PHEROMONE_PERIOD                 2
#define SLIME_PHEROMONE_DETECTION_RANGE             5
#define SLIME_PHEROMONE_TURN_ANGLE                  0.5
#define SLIME_PHEROMONE_LEVEL                       25
#define SLIME_IGNORE_SELF_PHEROMONE

// Slime direction alignment settings
//#define SLIME_ALIGN_DIRECTION
#define SLIME_OTHER_DETECTION_RANGE                 SLIME_PHEROMONE_DETECTION_RANGE
#define SLIME_ALIGN_TURN_ANGLE                      0.1

// Slime random rotation settings
#define SLIME_RANDOM_ROTATION_CHANCE                0.1
#define SLIME_RANDOM_ROTATION_ANGLE                 1

// Slime default direction settings
#define SLIME_BIAS_DIRECTION
#define SLIME_BIAS_DIRECTION_X                      GRID_WIDTH / 2
#define SLIME_BIAS_DIRECTION_Y                      GRID_HEIGHT / 2
#define SLIME_BIAS_ROTATION_ANGLE                   0.01

// Pheromones settings
#define PHEROMONE_MAX_LEVEL                         1000
#define PHEROMONE_HIGH_LEVEL_DIFFUSION_MULTIPLIER   0.5
#define PHEROMONE_LOW_LEVEL_DIFFUSION_MULTIPLIER    0
#define PHEROMONE_DIFFUSION_CONSTANT                5
#define PHEROMONE_MAX_LEVEL_RESET_VALUE             PHEROMONE_MAX_LEVEL

// Parameters settings
#define PARAMETER_FILE_NAME                         "parameters.txt"

#endif // CONSTANTS_H
