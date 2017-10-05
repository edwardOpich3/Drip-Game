using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace Object_Formation_Editor
{
	public partial class Form1 : Form
	{
		private void panel1_DragDrop(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.Bitmap))
			{
				objects.Add(new Object());
				objects[objects.Count - 1].sprite = e.Data.GetData(DataFormats.Bitmap) as Image;

				if (powerup == 0)
				{
					objects[objects.Count - 1].bounds = new Rectangle(getMousePosInPanel(), new Size((int)(128 * formationScale), (int)(128 * formationScale)));
				}
				else if (powerup == 1)
				{
					objects[objects.Count - 1].bounds = new Rectangle(getMousePosInPanel(), new Size((int)(32 * formationScale), (int)(32 * formationScale)));
				}

				objects[objects.Count - 1].bounds.X -= (objects[objects.Count - 1].Center.X);
				objects[objects.Count - 1].bounds.Y -= (objects[objects.Count - 1].Center.Y);

				objects[objects.Count - 1].angle = 0.0f;

				if (powerup == 0)
				{
					objects[objects.Count - 1].scale = (objects[objects.Count - 1].bounds.Width / 128.0f) / formationScale;
				}
				else if (powerup == 1)
				{
					objects[objects.Count - 1].scale = (objects[objects.Count - 1].bounds.Width / 32.0f) / formationScale;
				}

				objects[objects.Count - 1].type = type;
				objects[objects.Count - 1].powerup = powerup;

				changed = true;
				selected = objects.Count - 1;

				angle = objects[objects.Count - 1].angle;
				x = (objects[objects.Count - 1].bounds.X + objects[objects.Count - 1].Center.X) / formationScale;
				y = (objects[objects.Count - 1].bounds.Y + objects[objects.Count - 1].Center.Y) / formationScale;

				if (objects[objects.Count - 1].powerup == 0)
				{
					width = (objects[objects.Count - 1].bounds.Width / 128.0f) / formationScale;
					height = (objects[objects.Count - 1].bounds.Height / 128.0f) / formationScale;
				}
				else if (objects[objects.Count - 1].powerup == 1)
				{
					width = (objects[objects.Count - 1].bounds.Width / 32.0f) / formationScale;
					height = (objects[objects.Count - 1].bounds.Height / 32.0f) / formationScale;
				}

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

				background.Invalidate();
			}
		}

		private void background_MouseMove(object sender, EventArgs e)
		{
			if (leftMouseDown && selected >= 0)
			{
				switch (dragFuncComboBox.SelectedIndex)
				{
					// Position
					case 0:
						{
							objects[selected].bounds.Location = PointToClient(new Point(
								PointToScreen(getMousePosInPanel()).X - objects[selected].Center.X,
								PointToScreen(getMousePosInPanel()).Y - objects[selected].Center.Y));

							x = (objects[selected].bounds.X + objects[selected].Center.X) / formationScale;
							xTextBox.Text = x.ToString();

							y = (objects[selected].bounds.Y + objects[selected].Center.Y) / formationScale;
							yAndAngleTextBox.Text = y.ToString();

							background.Invalidate();
							break;
						}

					// Angle
					case 1:
						{
							objects[selected].angle = -(float)System.Windows.Vector.AngleBetween(new System.Windows.Vector(0, 1), new System.Windows.Vector(getMousePosInPanel().X - (objects[selected].bounds.X + objects[selected].Center.X), getMousePosInPanel().Y - (objects[selected].bounds.Y + objects[selected].Center.Y)));

							xTextBox.Text = "0";

							angle = objects[selected].angle;
							yAndAngleTextBox.Text = angle.ToString();

							background.Invalidate();
							break;
						}

					// Scale
					case 2:
						{
							System.Windows.Vector distance = new System.Windows.Vector(getMousePosInPanel().X - (objects[selected].bounds.X + objects[selected].Center.X), getMousePosInPanel().Y - (objects[selected].bounds.Y + objects[selected].Center.Y));

							/*objects[selected].bounds.X -= (int)(distance.X - (getMousePosInPanel().X - (objects[selected].bounds.X + objects[selected].Center.X)));
							objects[selected].bounds.Y -= (int)(distance.Y - (getMousePosInPanel().Y - (objects[selected].bounds.Y + objects[selected].Center.Y)));

							objects[selected].bounds.Width = (int)(distance.Length / 1.0);
							objects[selected].bounds.Height = (int)(distance.Length / 1.0);*/

							objects[selected].bounds.Inflate((int)(distance.Length - objects[selected].bounds.Width), (int)(distance.Length - objects[selected].bounds.Height));

							if (objects[selected].powerup == 0)
							{
								objects[objects.Count - 1].scale = (objects[objects.Count - 1].bounds.Width / 128.0f) / formationScale;
								width = (objects[selected].bounds.Width / 128.0f) / formationScale;
								height = (objects[selected].bounds.Height / 128.0f) / formationScale;
							}

							else if (objects[selected].powerup == 1)
							{
								objects[objects.Count - 1].scale = (objects[objects.Count - 1].bounds.Width / 32.0f) / formationScale;
								width = (objects[selected].bounds.Width / 32.0f) / formationScale;
								height = (objects[selected].bounds.Height / 32.0f) / formationScale;
							}

							xTextBox.Text = width.ToString();
							yAndAngleTextBox.Text = height.ToString();

							background.Invalidate();
							break;
						}
				}

				changed = true;
			}
		}

		private void background_MouseUp(object sender, EventArgs e)
		{
			leftMouseDown = false;

			if (selected >= 0)
			{
				switch (dragFuncComboBox.SelectedIndex)
				{
					// Position
					case 0:
						{
							break;
						}

					// Angle
					case 1:
						{
							break;
						}

					// Scale
					case 2:
						{
							/*double distance = Math.Sqrt(Math.Pow(getMousePosInPanel().X - (objects[selected].bounds.X + objects[selected].Center.X), 2) + Math.Pow(getMousePosInPanel().Y - (objects[selected].bounds.Y + objects[selected].Center.Y), 2));

							objects[selected].bounds.Inflate(objects[selected].bounds.Size.Width - (int)distance, objects[selected].bounds.Size.Height - (int)distance);

							background.Invalidate();*/
							break;
						}
				}
			}
		}

		private void background_Paint(object sender, PaintEventArgs e)
		{
			e.Graphics.DrawImage(background.Image, new Rectangle(new Point(0, 0), new Size((int)(1024.0f * formationScale), (int)(1024.0f * formationScale))));
			e.Graphics.DrawImage(background.Image, new Rectangle(new Point((int)(1024.0f * formationScale), 0), new Size((int)(1024.0f * formationScale), (int)(1024.0f * formationScale))));
			e.Graphics.DrawImage(background.Image, new Rectangle(new Point(0, (int)(1024.0f * formationScale)), new Size((int)(1024.0f * formationScale), (int)(1024.0f * formationScale))));
			e.Graphics.DrawImage(background.Image, new Rectangle(new Point((int)(1024.0f * formationScale), (int)(1024.0f * formationScale)), new Size((int)(1024.0f * formationScale), (int)(1024.0f * formationScale))));

			if (objects.Count > 0)
			{
				for (int i = 0; i < objects.Count; i++)
				{
					e.Graphics.ResetTransform();
					e.Graphics.TranslateTransform(objects[i].Center.X + objects[i].bounds.X, objects[i].Center.Y + objects[i].bounds.Y);
					e.Graphics.RotateTransform(-objects[i].angle);
					e.Graphics.TranslateTransform(-(objects[i].Center.X + objects[i].bounds.X), -(objects[i].Center.Y + objects[i].bounds.Y));
					e.Graphics.DrawImage(objects[i].sprite, objects[i].bounds);
					e.Graphics.ResetTransform();
				}
			}
		}
	}
}
