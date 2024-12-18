/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 00:04:32 by sota              #+#    #+#             */
/*   Updated: 2024/12/17 21:29:34 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIST_H
# define FT_LIST_H

# include <stddef.h>

/**
 * @struct t_list
 * @brief 双方向循環リストの各要素の構造体
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

/**
 * @brief リスト先頭に新しいノードを追加する
 *
 * @param head リストの先頭ポインタへのポインタ
 * @param new 追加する新しいノードのポインタ
 *
 * 先頭に新しいノードを追加する。
 * リストが空の場合は、新しいノードが最初の要素になる。
 */
void	ft_list_push_front(t_list **head, t_list *new);

/**
 * @brief リスト末尾に新しいノードを追加する
 *
 * @param head リストの先頭ポインタへのポインタ
 * @param new 追加する新しいノードのポインタ
 *
 * 末尾に新しいノードを追加する。
 * リストが空の場合は、新しいノードが最初の要素になる。
 */
void	ft_list_push_back(t_list **head, t_list *new);

/**
 * @brief リスト先頭のノードを取り出す
 *
 * @param head リストの先頭ポインタへのポインタ
 *
 * 先頭のノードを取り出す。
 * リストが空か、空になった場合は NULL を返す。
 */
t_list	*ft_list_pop_front(t_list **head);

/**
 * @brief リスト先頭のノードを取り出す
 *
 * @param head リストの先頭ポインタへのポインタ
 *
 * 末尾のノードを取り出す。
 * リストが空か、空になった場合は NULL を返す。
 */
t_list	*ft_list_pop_back(t_list **head);

/**
 * @brief リストを全てクリアする
 *
 * @param head リストの先頭ポインタへのポインタ
 * @param del 各ノードの content をクリアする関数
 *
 * 全ノードに対して、content に del を適用し、ノードを free する。
 * del が NULL の場合は content に対しては何もしない。
 *
 * 関数適用後、head が示す先は NULL となる。
 */
void	ft_list_clear(t_list **head, void (*del)(void *));

/**
 * @brief ノードを削除する
 * 
 * @param node 削除したいノードのポインタ
 * @param del ノードの content をクリアする関数
 *
 * 指定したノードに対して、content に del を適用し、ノードを free する。
 * del が NULL の場合は content に対しては何もしない。
 */
void	ft_list_delete(t_list *node, void (*del)(void *));

/**
 * @brief 各ノードに関数を適用する
 *
 * @param head リストの先頭へのポインタ
 * @param f 各ノードの content に適用する関数
 *
 * 全ノードに対して、content に f を適用する。
 * f が NULL のときは何もしない。
 */
void	ft_list_iter(t_list *head, void (*f)(void *));

/**
 * @brief 末尾のノードを返す
 *
 * @param head リストの先頭へのポインタ
 *
 * head->prev と等しい。head が NULL のときは NULL を返す。
 */
t_list	*ft_list_last(t_list *head);

/**
 * @brief 各ノードに関数を適用してできた新しいリストを作る
 *
 * @param head リストの先頭へのポインタ
 * @param f 各ノードの content に適用する関数
 * @param del 処理が失敗したときに各ノードの content をクリアする関数
 *
 * 各ノードに対して f を適用した新しいノードからなるリストを作る。
 *
 * head または f が NULL のときは何もしない。
 * 処理が失敗したときでも del が NULL のときは content に対しては何もしない。
 */
t_list	*ft_list_map(t_list *head, void *(*f)(void *), void (*del)(void *));

/**
 * @brief 新しいノードを作る
 *
 * @param content ノードが保持する値
 */
t_list	*ft_list_new(void *content);

/**
 * @brief リストのサイズ
 *
 * @param head リストの先頭へのポインタ
 */
size_t	ft_list_size(t_list *head);

#endif // FT_LIST_H
