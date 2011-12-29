#include "FluidRenderer2D.h"
#include <cstdio>

FluidRenderer2D::FluidRenderer2D(const FluidSolver2D &solver,
				 QWidget *parent)
  : FluidRenderer(FluidRenderer2D::getFormat(), parent),
    _solver(solver)
{}


FluidRenderer2D::~FluidRenderer2D()
{}


QGLFormat FluidRenderer2D::getFormat()
{
  // Specify the necessary OpenGL context attributes for this renderer.
  QGLFormat glFormat;
  glFormat.setVersion(2, 1);
  return glFormat;
}


void FluidRenderer2D::initializeGL()
{
  // Old-fashioned OpenGL here. Rewrite for CORE profile.
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_SMOOTH);

  // Set the clear color.
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  // Setup scene orientation.
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -10.0f);
}


void FluidRenderer2D::resizeGL(int width, int height)
{
  // Define viewport based on widget size.
  glViewport(0, 0, width, height);
  
  // Calculate an appropriate orthographic projection matrix to display the sim.
  unsigned simWidth = _solver.getSimulationWidth() + 2;
  unsigned simHeight = _solver.getSimulationHeight() + 2;

  float pixPerCellW = float(width) / float(simWidth);
  float pixPerCellH = float(height) / float(simHeight);

  float xMin = -1.0f;
  float xMax = xMin + simWidth;
  float yMin = -1.0;
  float yMax = yMin + simHeight;
  
  printf("W: %f,  H: %f\n", pixPerCellW, pixPerCellH);

  if (pixPerCellW > pixPerCellH) {
    // Width is the dominant dimension.
    yMin *= float(height) / float(width);
    yMax *= float(height) / float(width);
  }
  else {
    // Height is the dominant dimension.
    xMin *= float(width) / float(height);
    xMax *= float(width) / float(height);
  }
  
  // Define projection matrix based on widget size.
  glPushAttrib(GL_MATRIX_MODE);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xMin, xMax, yMin, yMax, 5.0, 15.0);
  glPopAttrib();
}


void FluidRenderer2D::paintGL()
{
  // Clear the existing framebuffer contents.
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Push the current modelview matrix onto the stack.
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Provide a self-reference to the fluid solver for rendering its data.
  _solver.draw(this);

  // Restore the previous modelview matrix.
  glPopMatrix();
}


void FluidRenderer2D::drawGrid2D(const Grid2D &grid)
{
  float height = grid.getRowCount();
  float width  = grid.getColCount();

  // Draw the vertical and horizontal grid lines.
  glPushAttrib(GL_CURRENT_BIT);
  glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
  glBegin(GL_LINES);
  for (unsigned i = 0; i <= grid.getColCount(); ++i) {
    glVertex2f(i, 0);
    glVertex2f(i, height);
  }
  for (unsigned i = 0; i <= grid.getRowCount(); ++i) {
    glVertex2f(0, i);
    glVertex2f(width, i);
  }
  glEnd();
  glPopAttrib();

  // Draw the cells based on the 

}
