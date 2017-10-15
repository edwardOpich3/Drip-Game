using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.IO;

namespace Object_Formation_Editor
{
	public partial class Form1 : Form
	{
		private void saveToolStripMenuItem_Click(object sender, EventArgs e)
		{
			// User chose to save
			if (saveFileDialog1.ShowDialog() != DialogResult.Cancel)
			{
				// If there's no filename, close the dialog, there's nothing to do here.
				if (saveFileDialog1.FileName == null)
				{
					Close();
				}

				// Now saving file with user's input file name
				writeStream = File.OpenWrite(saveFileDialog1.FileName);
				writeStream.SetLength(0);
				writer = new BinaryWriter(writeStream);
				for (int i = 0; i < objects.Count; i++)
				{
					// If the data is completely outside of the level, it's useless and unreachable; don't bother saving it.
					// If the type doesn't exist, then it's corrupt; get rid of it (TODO: That functionality doesn't quite work yet because there are two lists of objects; obstacles and powerups. Fix it!)
					if (objects[i].bounds.X / 2 < (2048.0f * formationScale) && (objects[i].bounds.X + objects[i].bounds.Width) / 2 > 0 && (objects[i].bounds.Y + objects[i].bounds.Height) / 2 > 0 && objects[i].bounds.Y / 2 < (2048.0f * formationScale) && objects[i].type >= 0 && objects[i].powerup > -1 && objects[i].powerup <= 1)
					{
						writer.Write(objects[i].powerup);
						writer.Write(objects[i].type);
						writer.Write((int)((objects[i].bounds.X + objects[i].Center.X) / formationScale));
						writer.Write((int)((objects[i].bounds.Y + objects[i].Center.Y) / formationScale));
						writer.Write(objects[i].scale);
						writer.Write(objects[i].angle);
					}
				}
				writer.Close();
				changed = false;
			}
		}

		private void openToolStripMenuItem_Click(object sender, EventArgs e)
		{
			// If the user ever hits cancel, just abandon the whole oparation!
			bool cancel = false;

			// The formation was changed; ask if they'd like to save first!
			if (changed)
			{
				DialogResult save = MessageBox.Show("Would you like to save your work?", "Save?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);

				// TODO: Put the save code in a special function so we don't have to copy-paste!
				if (save == DialogResult.Yes)
				{
					// User chose to save
					if (saveFileDialog1.ShowDialog() != DialogResult.Cancel)
					{
						if (saveFileDialog1.FileName == null)
						{
							Close();
						}

						writeStream = File.OpenWrite(saveFileDialog1.FileName); // Now saving file with user's input file name
						writeStream.SetLength(0);
						writer = new BinaryWriter(writeStream);
						for (int i = 0; i < objects.Count; i++)
						{
							// If the data is completely outside of the level, it's useless and unreachable; don't bother saving it.
							// If the type doesn't exist, then it's corrupt; get rid of it
							if (objects[i].bounds.X / 2 < (2048.0f * formationScale) && (objects[i].bounds.X + objects[i].bounds.Width) / 2 > 0 && (objects[i].bounds.Y + objects[i].bounds.Height) / 2 > 0 && objects[i].bounds.Y / 2 < (2048.0f * formationScale) && objects[i].type >= 0 && objects[i].powerup > -1 && objects[i].powerup <= 1)
							{
								writer.Write(objects[i].powerup);
								writer.Write(objects[i].type);
								writer.Write((int)((objects[i].bounds.X + objects[i].Center.X) / formationScale));
								writer.Write((int)((objects[i].bounds.Y + objects[i].Center.Y) / formationScale));
								writer.Write(objects[i].scale);
								writer.Write(objects[i].angle);
							}
						}
						writer.Close();
						changed = false;
					}
				}
				else if (save == DialogResult.Cancel)
				{
					cancel = true;
				}
			}
			if (!cancel)
			{
				// Open the file open dialog
				if (openFileDialog1.ShowDialog() != DialogResult.Cancel)
				{
					// If there's no filename, there's nothing to do here.
					if (openFileDialog1.FileName == null)
					{
						Close();
					}

					// Prepare the objects list for the new formation!
					for (int i = 0; i < objects.Count; i++)
					{
						objects[i].sprite.Dispose();
					}
					objects.Clear();

					// Now loading file with user's input file name
					readStream = File.OpenRead(openFileDialog1.FileName);
					reader = new BinaryReader(readStream);
					for (int i = 0; readStream.Position < readStream.Length; i++)
					{
						objects.Add(new Object());
						objects[i].powerup = reader.ReadInt32();
						objects[i].type = reader.ReadInt32();
						objects[i].bounds.Location = new Point((int)(reader.ReadInt32() * formationScale), (int)(reader.ReadInt32() * formationScale));
						objects[i].scale = reader.ReadSingle();

						if (objects[i].powerup == 0)
						{
							objects[i].bounds.Size = new Size((int)((objects[i].scale * 128.0f) * formationScale), (int)((objects[i].scale * 128.0f) * formationScale));
						}
						else if (objects[i].powerup == 1)
						{
							objects[i].bounds.Size = new Size((int)((objects[i].scale * 32.0f) * formationScale), (int)((objects[i].scale * 32.0f) * formationScale));
						}

						objects[i].angle = reader.ReadSingle();

						objects[i].bounds.X -= objects[i].Center.X;
						objects[i].bounds.Y -= objects[i].Center.Y;

						switch (objects[i].powerup)
						{
							case 0:
							{
								objects[i].sprite = (Image)obstacleList[objects[i].type].Image.Clone();
								break;
							}

							case 1:
							{
								objects[i].sprite = (Image)powerupList[objects[i].type].Image.Clone();
								break;
							}
						}
					}
					reader.Close();
					changed = false;
					background.Invalidate();
				}
			}
		}

		private void newToolStripMenuItem_Click(object sender, EventArgs e)
		{
			bool cancel = false;

			// The file was changed, ask the user if they'd like to save before losing their progress!
			if (changed)
			{
				DialogResult save = MessageBox.Show("Would you like to save your work?", "Save?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
				if (save == DialogResult.Yes)
				{
					// User chose to save
					if (saveFileDialog1.ShowDialog() != DialogResult.Cancel)
					{
						if (saveFileDialog1.FileName == null)
						{
							Close();
						}

						writeStream = File.OpenWrite(saveFileDialog1.FileName); // Now saving file with user's input file name
						writeStream.SetLength(0);
						writer = new BinaryWriter(writeStream);
						for (int i = 0; i < objects.Count; i++)
						{
							// If the data is completely outside of the level, it's useless and unreachable; don't bother saving it.
							// If the type doesn't exist, then it's corrupt; get rid of it
							if (objects[i].bounds.X / 2 < (2048.0f * formationScale) && (objects[i].bounds.X + objects[i].bounds.Width) / 2 > 0 && (objects[i].bounds.Y + objects[i].bounds.Height) / 2 > 0 && objects[i].bounds.Y / 2 < (2048.0f * formationScale) && objects[i].type >= 0 && objects[i].powerup > -1 && objects[i].powerup <= 1)
							{
								writer.Write(objects[i].powerup);
								writer.Write(objects[i].type);
								writer.Write((int)((objects[i].bounds.X + objects[i].Center.X) / formationScale));
								writer.Write((int)((objects[i].bounds.Y + objects[i].Center.Y) / formationScale));
								writer.Write(objects[i].scale);
								writer.Write(objects[i].angle);
							}
						}
						writer.Close();
						changed = false;
					}
				}
				else if (save == DialogResult.Cancel)
				{
					cancel = true;
				}
			}

			// If the operation wasn't canceled, delete all the objects
			if (!cancel)
			{
				for (int i = 0; i < objects.Count; i++)
				{
					objects[i].sprite.Dispose();
				}
				objects.Clear();
				changed = false;

				background.Invalidate();
			}
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void closeButton_Click(object sender, FormClosingEventArgs e)
		{
			// The user has work they need to save!
			if (changed)
			{
				DialogResult save = MessageBox.Show("Would you like to save your work?", "Save?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
				if (save == DialogResult.Yes)
				{
					// User chose to save
					if (saveFileDialog1.ShowDialog() != DialogResult.Cancel)
					{
						if (saveFileDialog1.FileName == null)
						{
							Close();
						}

						writeStream = File.OpenWrite(saveFileDialog1.FileName); // Now saving file with user's input file name
						writeStream.SetLength(0);
						writer = new BinaryWriter(writeStream);
						for (int i = 0; i < objects.Count; i++)
						{
							// If the data is completely outside of the level, it's useless and unreachable; don't bother saving it.
							// If the type doesn't exist, then it's corrupt; get rid of it
							if (objects[i].bounds.X / 2 < (2048.0f * formationScale) && (objects[i].bounds.X + objects[i].bounds.Width) / 2 > 0 && (objects[i].bounds.Y + objects[i].bounds.Height) / 2 > 0 && objects[i].bounds.Y / 2 < (2048.0f * formationScale) && objects[i].type >= 0 && objects[i].powerup > -1 && objects[i].powerup <= 1)
							{
								writer.Write(objects[i].powerup);
								writer.Write(objects[i].type);
								writer.Write((int)((objects[i].bounds.X + objects[i].Center.X) / formationScale));
								writer.Write((int)((objects[i].bounds.Y + objects[i].Center.Y) / formationScale));
								writer.Write(objects[i].scale);
								writer.Write(objects[i].angle);
							}
						}
						writer.Close();
						changed = false;
					}
					e.Cancel = false;
				}
				else if (save == DialogResult.No)
				{
					e.Cancel = false;
				}
				else if (save == DialogResult.Cancel)
				{
					e.Cancel = true;
				}
			}
		}
	}
}
