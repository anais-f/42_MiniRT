
	// printf("Hello Nana_ïs\n");
	// while (y <= i_height)
	// {
	// 	x = 0;
	// 	while (x <= i_width)
	// 	{
	// 		my_mlx_pixel_put(&img, x, y, 0x00FF00F0);
	// 		x++;
	// 	}
	// 	y++;
	// }
	// int cx = 540; // Centre en x (coordonnée centrale)
	// int cy = 540; // Centre en y (coordonnée centrale)
	// int r = 100;  // Rayon du cercle
	// int lx = 440; // Position x de la lumière
	// int ly = 440; // Position y de la lumière

	// y = cy - r;
	// while (y <= cy + r)
	// {
	// 	x = cx - r;
	// 	while (x <= cx + r)
	// 	{
	// 		// Calculer si le point est à l'intérieur du cercle (surface de la sphère)
	// 		int dx = x - cx; // = (x - decalage)
	// 		int dy = y - cy; // = (y - decalage)
	// 		if (dx * dx + dy * dy <= r * r) // equation cercle 
	// 		{
	// 			// Calculer la normale au point (x, y)
	// 			float nx = dx / (float)r;
	// 			float ny = dy / (float)r;

	// 			// Calculer la direction de la lumière
	// 			float lx_norm = (lx - x) / (float)r;
	// 			float ly_norm = (ly - y) / (float)r;

	// 			// Calculer l'intensité de la lumière en fonction de la normale
	// 			float dot_product = (nx * lx_norm + ny * ly_norm);
	// 			float intensity = fmax(0, dot_product); // L'intensité est comprise entre 0 et 1

	// 			// Couleur avec dégradé (0xFFFFFF est blanc pur, multiplié par l'intensité)
	// 			int color = (int)(intensity * 255) << 16 | (int)(intensity * 255) << 8 | (int)(intensity * 255);

	// 			// Dessiner le pixel avec la couleur calculée
	// 			my_mlx_pixel_put(&img, x, y, color); //color
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }














/***********************************************************************************/
	// y = 0;
	// while (y <= cy + r)
	// {
	// 	x = 0;
	// 	while (x <= cx + r)
	// 	{
	// 		// Vérifier si le point (x, y) est dans le cercle
	// 		// if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= r * r)
	// 		if ((x - 540) * (x - 540) + (y - 540) * (y - 540) <= r * r)
	// 		{
	// 			my_mlx_pixel_put(&data, x, y, 0x00FF0000); // Dessiner le pixel rouge si dans le cercle
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }

	// while (y <= i_height)
	// {
	// 	while (x <= i_width)
	// 	{
	// 		my_mlx_pixel_put(&data, x, y, 0x00FF0000);
	// 		x++;
	// 	}
	// 	y++;
	// 	x = 440;
 	// }
	/*********************************************************************************/