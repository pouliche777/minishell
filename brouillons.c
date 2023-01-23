void	check_dollar(t_shell *shell, int i)
{
	int	j;

	j = 0;

	while (shell->cmds[i][j])
	{
		if (shell->cmds[i][j][0] == '$' && shell->cmds[i][j][0] == '\0')
			put_variable(shell, i, j);
		j++;
	}
}

void	put_variable(t_shell *shell, int i, int j)
{
	int		h;
	char	*variable;

	variable = shell->cmds[i][j + 1];
	h = 0;
	while (shell->env[h])
	{
		if (ft_strncmp(shell->env[h], variable, ft_strlen(variable)) == 0)
			modify_command_2(shell, shell->env[h][ft_strlen(variable)], i, j);
		else
			exit(1);
	}
}

void	modify_command_2(t_shell *shell, char *contenu_variable, int i, int j)
{
	char	**cmd_tempo;
	int		h;

	h = 0;
	cmd_tempo = malloc(sizeof(shell->cmds[i]));
	while (shell->cmds[i][h])
	{
		cmd_tempo[h] = ft_strdup(shell->cmds[i][h]);
		h++;
	}
	free (shell->cmds[i]);
	h = 0;
	while (cmd_tempo[h])
	{
		if (h == j)
		{
			shell->cmds[i][h] = ft_strdup(contenu_variable);
			h++;
		}
		else
			shell->cmds[i][h] = ft_strdup(cmd_tempo[h]);
		h++;
	}
	free (cmd_tempo);
}