using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace Object_Formation_Editor
{
	public partial class Form1 : Form
	{
		// File I/O Objects
		BinaryReader reader;
		BinaryWriter writer;
		Stream readStream;
		Stream writeStream;

		// All lists are sorted from furthest to closest to the screen; lower indices will be drawn first.

		List<PictureBox> obstacleList;	// The list of obstacles in the obstacles tab
		List<PictureBox> powerupList;   // The list of powerups in the powerups tab
		List<Object> objects;           // The list of objects on the screen;

		PictureBox background;

		bool leftMouseDown;				// Is the left mouse button currently pressed?
		bool changed;                   // Has the file been changed since creation/load?

		int type = -1;					// Which item in the list is the object?
		int powerup = -1;				// Is the object a powerup or obstacle?
		float angle = 0.0f;
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;

		int selected = -1;              // The index of the object currently selected. If -1, no object is selected.
		float formationScale = 1;		// The scale of the formation preview; 1 is actual size, 0.25 means the whole formation fits without needing to scroll.

		public Form1()
		{
			InitializeComponent();

			// Add some event handlers
			panel1.DragEnter += panel1_DragEnter;
			panel1.DragDrop += panel1_DragDrop;

			yAndAngleTextBox.TextChanged += yAndAngleTextBox_TextChanged;
			xTextBox.TextChanged += xTextBox_TextChanged;

			FormClosing += new FormClosingEventHandler(closeButton_Click);

			obstacleList = new List<PictureBox>();

			// Load in the obstacles
			String[] objectNames = Directory.GetFiles("data/objs/obstacles");
			for(int i = 0; i < objectNames.Length; i++)
			{
				obstacleList.Add(new PictureBox());
				obstacleList[obstacleList.Count - 1].Image = Image.FromFile(objectNames[i]);
				obstacleList[obstacleList.Count - 1].Parent = tabPage1;
				obstacleList[obstacleList.Count - 1].SetBounds((((i % 3) + 1) * 32) + ((i % 3) * 128), (((i / 3) + 1) * 32) + ((i / 3) * 128), 128, 128);
				obstacleList[obstacleList.Count - 1].SizeMode = PictureBoxSizeMode.Zoom;
				obstacleList[obstacleList.Count - 1].MouseDown += objectList_MouseDown;
			}

			// Load in the powerups
			powerupList = new List<PictureBox>();
			objectNames = Directory.GetFiles("data/objs/powerups");
			for(int i = 0; i < objectNames.Length; i++)
			{
				powerupList.Add(new PictureBox());
				powerupList[powerupList.Count - 1].Image = Image.FromFile(objectNames[i]);
				powerupList[powerupList.Count - 1].Parent = tabPage2;
				powerupList[powerupList.Count - 1].SetBounds((((i % 3) + 1) * 32) + ((i % 3) * 128), (((i / 3) + 1) * 32) + ((i / 3) * 128), 128, 128);
				powerupList[powerupList.Count - 1].SizeMode = PictureBoxSizeMode.CenterImage;
				powerupList[powerupList.Count - 1].MouseDown += objectList_MouseDown;
			}

			// This list of objects is unpopulated on startup, only when objects are dragged in or a file is loaded is it altered.
			objects = new List<Object>();

			// Load in the background
			background = new PictureBox();
			background.SetBounds(0, 0, 2048, 2048);
			background.Parent = panel1;
			background.Image = Image.FromFile(Directory.GetFiles("data/bgs")[0]);

			// Add some event handlers to the background
			background.Paint += background_Paint;
			background.MouseDown += background_MouseDown;
			background.MouseUp += background_MouseUp;
			background.MouseMove += background_MouseMove;
			background.KeyDown += background_KeyDown;

			// Set both of the drop downs to a default value
			dragFuncComboBox.SelectedIndex = 0;
			levelThemeComboBox.SelectedIndex = 0;

			// Set dragFuncComboBox's specific event handler
			dragFuncComboBox.SelectedIndexChanged += new System.EventHandler(dragFuncComboBox_SelectedIndexChanged);
		}

		private void Form1_Load(object sender, EventArgs e)
		{

		}

		private void dragFuncComboBox_SelectedIndexChanged(object sender, EventArgs e)
		{
			// Change the textboxes and their labels based on the new mouse-drag function
			switch(dragFuncComboBox.SelectedIndex)
			{
				// Position
				case 0:
				{
					if(yAndAngleLabel.Text == "angle")
					{
						yAndAngleLabel.Text = "y";
						yAndAngleLabel.Location = new Point(yAndAngleLabel.Location.X + 12, yAndAngleLabel.Location.Y);
						xLabel.Enabled = true;
						xTextBox.Enabled = true;
					}

					xTextBox.Text = x.ToString();
					yAndAngleTextBox.Text = y.ToString();
					break;
				}
				// Angle
				case 1:
				{
					if (yAndAngleLabel.Text != "angle")
					{
						xLabel.Enabled = false;
						xTextBox.Enabled = false;
						yAndAngleLabel.Text = "angle";
						yAndAngleLabel.Location = new Point(yAndAngleLabel.Location.X - 12, yAndAngleLabel.Location.Y);
					}

					xTextBox.Text = "0";
					yAndAngleTextBox.Text = angle.ToString();
					break;
				}
				// Scale
				case 2:
				{
					if (yAndAngleLabel.Text == "angle")
					{
						yAndAngleLabel.Text = "y";
						yAndAngleLabel.Location = new Point(yAndAngleLabel.Location.X + 12, yAndAngleLabel.Location.Y);
						xLabel.Enabled = true;
						xTextBox.Enabled = true;
					}

					xTextBox.Text = width.ToString();
					yAndAngleTextBox.Text = height.ToString();
					break;
				}
			}
		}

		private void objectList_MouseDown(object sender, EventArgs e)
		{
			PictureBox myPictureBox = sender as PictureBox;

			// Check if the mouse is actually clicking any of the objects in the current tab
			powerup = tabControl1.SelectedIndex;
			switch (powerup)
			{
				case 0: // Obstacle
				{
					for (int i = 0; i < obstacleList.Count; i++)
					{
						if (powerupList[i].Bounds.Contains(PointToClient(new Point(MousePosition.X + tabPage1.HorizontalScroll.Value - tabControl1.Location.X, MousePosition.Y + tabPage1.VerticalScroll.Value - tabControl1.Location.Y))))
						{
							type = i;
							break;
						}
					}
					break;
				}

				case 1: // Powerup
				{
					for (int i = 0; i < powerupList.Count; i++)
					{
						if (powerupList[i].Bounds.Contains(PointToClient(new Point(MousePosition.X + tabPage2.HorizontalScroll.Value - tabControl1.Location.X, MousePosition.Y + tabPage2.VerticalScroll.Value - tabControl1.Location.Y))))
						{
							type = i;
							break;
						}
					}
					break;
				}
			}

			// Prepare to drag and drop the selected object!
			myPictureBox.DoDragDrop(myPictureBox.Image.Clone(), DragDropEffects.Copy | DragDropEffects.Move);
		}

		private void panel1_DragEnter(object sender, DragEventArgs e)
		{
			if(e.Data.GetDataPresent(DataFormats.Bitmap))
			{
				e.Effect = DragDropEffects.Copy;
			}
			else
			{
				e.Effect = DragDropEffects.None;
			}
		}

		private void background_MouseDown(object sender, EventArgs e)
		{
			background.Focus();
			leftMouseDown = true;

			// Compare mouse's position to all of the objects in your list, starting from the end.
			for (int i = objects.Count - 1; i >= 0; i--)
			{
				if (objects[i].bounds.Contains(getMousePosInPanel()))
				{
					// If the mouse is in the bounds of any of them, that object is now selected.
					selected = i;

					angle = objects[i].angle;
					x = (objects[i].bounds.X + objects[i].Center.X) / formationScale;
					y = (objects[i].bounds.Y + objects[i].Center.Y) / formationScale;

					if (objects[i].powerup == 0)
					{
						width = (objects[i].bounds.Width / 128.0f) / formationScale;
						height = (objects[i].bounds.Height / 128.0f) / formationScale;
					}
					else if (objects[i].powerup == 1)
					{
						width = (objects[i].bounds.Width / 32.0f) / formationScale;
						height = (objects[i].bounds.Height / 32.0f) / formationScale;
					}

					break;
				}
				selected = i - 1;   // This will have the behavior of making selected -1 if nothing was clicked

				angle = 0;
				x = 0;
				y = 0;
				width = 0;
				height = 0;
			}

			// Update the textboxes' text based on the current mouse-drag function
			switch (dragFuncComboBox.SelectedIndex)
			{
				case 0:
				{
					xTextBox.Text = x.ToString();
					yAndAngleTextBox.Text = y.ToString();
					break;
				}

				case 1:
				{
					yAndAngleTextBox.Text = angle.ToString();
					break;
				}

				case 2:
				{
					xTextBox.Text = width.ToString();
					yAndAngleTextBox.Text = height.ToString();
					break;
				}
			}
		}

		private void background_KeyDown(object sender, KeyEventArgs e)
		{
			// If the user hit the delete key and there was an object selected, delete it and clear the text boxes
			if(e.KeyCode == Keys.Delete && selected >= 0)
			{
				objects[selected].sprite.Dispose();
				objects.RemoveAt(selected);
				selected = -1;

				angle = 0;
				x = 0;
				y = 0;
				width = 0;
				height = 0;

				switch (dragFuncComboBox.SelectedIndex)
				{
					case 0:
						{
							xTextBox.Text = x.ToString();
							yAndAngleTextBox.Text = y.ToString();
							break;
						}

					case 1:
						{
							xTextBox.Text = "0";
							yAndAngleTextBox.Text = angle.ToString();
							break;
						}

					case 2:
						{
							xTextBox.Text = width.ToString();
							yAndAngleTextBox.Text = height.ToString();
							break;
						}
				}
			}

			changed = true;

			background.Invalidate();
		}

		private void yAndAngleTextBox_TextChanged(object sender, EventArgs e)
		{
			// Update the current selected object (if there is one) to the new value
			switch(dragFuncComboBox.SelectedIndex)
			{
				// Position
				case 0:
				{
					float.TryParse(yAndAngleTextBox.Text, out y);
					if(selected >= 0)
					{
						objects[selected].bounds.Y = (int)((y * formationScale) - objects[selected].Center.Y);
						changed = true;
						background.Invalidate();
					}
					break;
				}

				// Angle
				case 1:
				{
					float.TryParse(yAndAngleTextBox.Text, out angle);
					if (selected >= 0)
					{
						objects[selected].angle = angle;
						changed = true;
						background.Invalidate();
					}
					break;
				}

				// Scale
				case 2:
				{
					float.TryParse(yAndAngleTextBox.Text, out height);
					if (selected >= 0)
					{
						/*objects[selected].bounds.Height = (int)(height * 128.0f);
						objects[selected].bounds.Width = (int)(height * 128.0f);*/

						if (objects[selected].powerup == 0)
						{
							objects[selected].bounds.Inflate((int)(((height * 128.0f * formationScale) - objects[selected].bounds.Height) / 2.0f), (int)(((height * 128.0f * formationScale) - objects[selected].bounds.Height) / 2.0f));
							objects[selected].scale = height;
						}

						else if (objects[selected].powerup == 1)
						{
							objects[selected].bounds.Inflate((int)(((height * 32.0f * formationScale) - objects[selected].bounds.Height) / 2.0f), (int)(((height * 32.0f * formationScale) - objects[selected].bounds.Height) / 2.0f));
							objects[selected].scale = height;
						}

						xTextBox.Text = yAndAngleTextBox.Text;
						changed = true;
						background.Invalidate();
					}
					break;
				}
			}
		}

		private void xTextBox_TextChanged(object sender, EventArgs e)
		{
			// Update the current selected object (if there is one) to the new value
			switch (dragFuncComboBox.SelectedIndex)
			{
				// Position
				case 0:
				{
					float.TryParse(xTextBox.Text, out x);
					if(selected >= 0)
					{
						objects[selected].bounds.X = (int)((x * formationScale) - objects[selected].Center.X);
						changed = true;
						background.Invalidate();
					}
					break;
				}

				// Scale
				case 2:
				{
					float.TryParse(xTextBox.Text, out width);
					if(selected >= 0)
					{
						/*objects[selected].bounds.Width = (int)(width * 128.0f);
						objects[selected].bounds.Height = (int)(width * 128.0f);*/

						if (objects[selected].powerup == 0)
						{
							objects[selected].bounds.Inflate((int)(((width * 128.0f * formationScale) - objects[selected].bounds.Width) / 2.0f), (int)(((width * 128.0f * formationScale) - objects[selected].bounds.Width) / 2.0f));
							objects[selected].scale = width;
						}

						else if (objects[selected].powerup == 1)
						{
							objects[selected].bounds.Inflate((int)(((width * 32.0f * formationScale) - objects[selected].bounds.Width) / 2.0f), (int)(((width * 32.0f * formationScale) - objects[selected].bounds.Width) / 2.0f));
							objects[selected].scale = width;
						}

						yAndAngleTextBox.Text = xTextBox.Text;
						changed = true;
						background.Invalidate();
					}
					break;
				}
			}
		}

		// Returns mouse position relative to the top left of the formation display
		private Point getMousePosInPanel()
		{
			return PointToClient(new Point(MousePosition.X + panel1.HorizontalScroll.Value - panel1.Location.X, MousePosition.Y + panel1.VerticalScroll.Value - panel1.Location.Y));
		}

		// Zooms in on the formation by a factor of 2
		private void plusButton_Click(object sender, EventArgs e)
		{
			formationScale *= 2.0f;
			if(formationScale > 1.0f)
			{
				formationScale = 1.0f;
			}
			else
			{
				for (int i = 0; i < objects.Count; i++)
				{
					objects[i].bounds = new Rectangle((int)(objects[i].bounds.X * 2.0f), (int)(objects[i].bounds.Y * 2.0f), (int)(objects[i].bounds.Width * 2.0f), (int)(objects[i].bounds.Height * 2.0f));
				}
			}

			background.SetBounds(-panel1.HorizontalScroll.Value, -panel1.VerticalScroll.Value, (int)(2048.0f * formationScale), (int)(2048.0f * formationScale));

			background.Invalidate();
		}
		
		// Zooms out on the formation by a factor of 2
		private void minusButton_Click(object sender, EventArgs e)
		{
			formationScale /= 2.0f;
			if(formationScale < 0.25f)
			{
				formationScale = 0.25f;
			}
			else
			{
				for (int i = 0; i < objects.Count; i++)
				{
					objects[i].bounds = new Rectangle((int)(objects[i].bounds.X / 2.0f), (int)(objects[i].bounds.Y / 2.0f), (int)(objects[i].bounds.Width / 2.0f), (int)(objects[i].bounds.Height / 2.0f));
				}
			}

			background.SetBounds(-panel1.HorizontalScroll.Value, -panel1.VerticalScroll.Value, (int)(2048.0f * formationScale), (int)(2048.0f * formationScale));

			background.Invalidate();
		}
	}
}
