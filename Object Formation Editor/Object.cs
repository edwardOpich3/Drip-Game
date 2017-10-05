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
		public Rectangle bounds;
		public float angle;
		public float scale;
		public int type;
		public int powerup;
		public Image sprite;
		public Point Center
		{
			get
			{
				return new Point((int)(bounds.Width / 2.0), (int)(bounds.Height / 2.0));
			}
		}
	}
}
