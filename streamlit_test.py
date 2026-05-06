import streamlit as st

st.title("Test App")

a = st.number_input("Enter A", step=1)
b = st.number_input("Enter B", step=1)

if st.button("Add"):
    st.write("Result:", a + b)