<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Device extends Model
{


	public function readings()
	{
		return $this->hasMany('App\Reading');
	}
}
