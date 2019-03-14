            partner = my_id ^ (int) pow(2,j);
 			Node.Node_Id = my_id;
 			msg_dest_tag = Node.Node_Id;
 			msg_src_tag = partner;
			if(partner<Nodes)
			{
                MPI_Sendrecv( 
                &message_buf,                   /* initial address of send buffer (choice) */
                size,                           /* number of elements in send buffer (integer) */
                MPI_INT,                        /* type of elements in send buffer (handle) */
                partner,                        /* rank of destination (integer) */
                msg_dest_tag,                   /* send tag (integer) */
                &recv_buf,                      /* address of the receive buffer (integer) */
                size,                           /* number of elements in receive buffer (integer) */
                MPI_INT,                        /* type of elements in receive buffer (handle) */
                partner,                        /* rank of source (integer) */
                msg_src_tag,                    /* receive tag (integer) */
                MPI_COMM_WORLD,                 /* communicator (handle) */
                &Status);
            }
