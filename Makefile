all:
	(cd libft; make)
	(cd src; make)

clean:
	(cd libft; make clean)
	(cd src; make clean)

fclean:
	(cd libft; make fclean)
	(cd src; make fclean)

re: fclean all
