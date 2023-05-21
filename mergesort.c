node* move(node* temp, int len, int* size) {
	int count;
	for (count = 0; count < len; count++) {
		if (temp == NULL || temp->next == NULL) {
			*size = count;
			return temp;
		}
		temp = temp->next;
	}
	*size = count;
	return temp;
}

node* merge(int len) {

	node* s_head = newnode;
	node* s_tail = newnode;
	s_head->next = s_tail;
	s_tail->next = NULL;

	node* ptr_l = newnode;
	node* ptr_r = newnode;
	node* next_ptr = newnode;
	node* curr = s_head;
	int is_start = 1;

	while (1) {

		int size_l, size_r;
		
		if (is_start == 1) {
			ptr_l = head->next;
			ptr_r = move(ptr_l, len, &size_l);
			next_ptr = move(ptr_r, len, &size_r);
			is_start = 0;
		}
		else {
			ptr_l = next_ptr;
			ptr_r = move(ptr_l, len, &size_l);
			next_ptr = move(ptr_r, len, &size_r);
		}

		if (size_r == 0) {
			while (size_l != 0) {
				node* sort = ptr_l;
				ptr_l = ptr_l->next;
				sort->next = curr->next;
				curr->next = sort;
				curr = curr->next;
				size_l--;
			}
			curr->next = s_tail;
			return s_head;
		}

		while (size_l != 0 && size_r != 0) {
			if (strcmp(ptr_l->data.name, ptr_r->data.name) < 0) { // here is comparing part. modify and use it.
				node* sort = ptr_l;
				ptr_l = ptr_l->next;
				sort->next = curr->next;
				curr->next = sort;
				curr = curr->next;
				size_l--;
			}
			else {
				node* sort = ptr_r;
				ptr_r = ptr_r->next;
				sort->next = curr->next;
				curr->next = sort;
				curr = curr->next;
				size_r--;
			}
		}

		if (size_l == 0) {
			while (size_r != 0) {
				node* sort = ptr_r;
				ptr_r = ptr_r->next;
				sort->next = curr->next;
				curr->next = sort;
				curr = curr->next;
				size_r--;
			}
		}
		else {
			while (size_l != 0) {
				node* sort = ptr_l;
				ptr_l = ptr_l->next;
				sort->next = curr->next;
				curr->next = sort;
				curr = curr->next;
				size_l--;
			}
		}

		if (ptr_r == NULL || ptr_r->next == NULL) {
			curr->next = s_tail;
			return s_head;
		}

	}

}

void SortByName_SL() {

	printf("Sorting...\n");

	int len = 1;
	while (1) {

		head = merge(len);
		len *= 2;

		if (len > list_size) {
			break;
		}
	}

	printf("Sorting Complete\n");
}
