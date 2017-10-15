using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Object_Formation_Editor
{
	class Object
	{
		public Rectangle bounds;	// The rectangle defining where the sprite is drawn
		public float angle;			// The angle to be drawn at; 0 is down, and increasing rotates counter-clockwise
		public float scale;			// The scale to draw the image at; 1 = 128 pixels width
		public int type;			// The type index of the object
		public int powerup;			// Is the object a powerup, obstacle, or invalid type?
		public Image sprite;		// The object's sprite

		// Returns the point at the center of the object, it's official X/Y position
		public Point Center
		{
			get
			{
				return new Point((int)(bounds.Width / 2.0), (int)(bounds.Height / 2.0));
			}
		}
	}
}
