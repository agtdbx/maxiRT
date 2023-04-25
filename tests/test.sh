
PATH="$(realpath "$(dirname "$0")"/..):$PATH"

function test__no_extension
{

	cat <<-EOF | assertEquals "$(cat)" "$(minirt ./no_extension)"
		Error
		<./no_extension>: Invalid filename: Bad extension
	EOF
}

function test__bad_extensions
{

	cat <<-EOF | assertEquals "$(cat)" "$(minirt ./no_extension.)"
		Error
		<./no_extension.>: Invalid filename: Bad extension
	EOF

	cat <<-EOF | assertEquals "$(cat)" "$(minirt ./no_extension.l)"
		Error
		<./no_extension.l>: Invalid filename: Bad extension
	EOF

	cat <<-EOF | assertEquals "$(cat)" "$(minirt ./no_extension.rta)"
		Error
		<./no_extension.rta>: Invalid filename: Bad extension
	EOF
}

source shunit2
